/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:40:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/28 15:13:16 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_fill_token_command(t_asm_data *asm_data, char *line, t_token *token)
{
	if (line[0] == LABEL_CHAR && line[1] != '\0')
	{
		token->type = Label_arg;
		return ;
	}
	if (ft_line_is_command(line) != 0)
	{
		token->type = Command;
		return ;
	}
	token->type = Unknown;
	ft_error_add(asm_data, ft_strjoin_orig("Unknown type of token ",\
	token->str), token->col, 2);
}

void	ft_fill_token_reg(t_asm_data *asm_data, char *line, t_token *token)
{
	long long	temp;

	temp = ft_atol(&line[1]);
	if (line[0] == 'r')
	{
		token->type = Unknown;
		if (!line[1])
			ft_error_add(asm_data, ft_strjoin_orig("No value in reg ",\
			token->str), token->col, 2);
		else if (!ft_string_contain_only_num(&line[1]))
			ft_error_add(asm_data, ft_strjoin_orig("Detected Char in reg  ",\
			token->str), token->col, 1);
		else if (temp < 0 || temp > REG_NUMBER)
			ft_error_add(asm_data, ft_strjoin_orig("Wrong reg num ",\
			token->str), token->col, 2);
		else
			token->type = Register;
		return ;
	}
	ft_fill_token_command(asm_data, line, token);
}

void	ft_fill_token_direct(t_asm_data *asm_data, char *line, t_token *token)
{
	if (line[0] == DIRECT_CHAR)
	{
		if (line[1] == LABEL_CHAR)
			ft_fill_token_direct_labels(asm_data, &line[2], token);
		else if (ft_isdigit(line[1]) || line[1] == '+' || line[1] == '-')
			ft_fill_token_direct_digits(asm_data, &line[1], token);
		else
		{
			token->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Unknown value in \
DIRECT_ADDR ", token->str), token->col, 2);
		}
		return ;
	}
	ft_fill_token_reg(asm_data, line, token);
}

void	ft_fill_token_digits(t_asm_data *asm_data, char *line, t_token *token)
{
	if (ft_isdigit(line[0]) || line[0] == '+' || line[0] == '-')
	{
		token->type = Unknown;
		if (line[0] == '+')
			ft_error_add(asm_data, ft_strjoin_orig("Detected plus in number ",\
			token->str), token->col, 1);
		else if (!ft_string_contain_only_num(line) && ft_atol(line) != 0)
			ft_error_add(asm_data, ft_strjoin_orig("Detected chars in number ",\
			token->str), token->col, 1);
		else
			token->type = Number;
		return ;
	}
	ft_fill_token_direct(asm_data, line, token);
}

void	ft_fill_token(t_asm_data *asm_data, char *line, t_token *token)
{
	token->str = line;
	if (line[0] == ' ' || line[0] == '\t')
	{
		token->type = Whitespace;
		return ;
	}
	if (line[0] == SEPARATOR_CHAR)
	{
		token->type = Separator;
		return ;
	}
	if (ft_find_sym(line, LABEL_CHAR) && line[0] != DIRECT_CHAR)
	{
		if (ft_check_label_symbols(line))
			token->type = Label;
		else
		{
			token->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Wrong symbols in label ",\
			token->str), token->col, 1);
		}
		return ;
	}
	ft_fill_token_digits(asm_data, line, token);
}
