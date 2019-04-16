/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:40:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 19:01:18 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_fill_token_command(t_asm_data *asm_data, char *line)
{
	// проверяем строку на принадлежность командам
	TOKEN_DATA->type = Unknown;
	ft_error_add(asm_data, ft_strjoin_orig("Unknown type of token ",\
	TOKEN_DATA->str), TOKEN_DATA->col, 1);
}

void	ft_fill_token_reg(t_asm_data *asm_data, char *line, long long temp)
{
	temp = ft_atol(&line[1]);
	if (line[0] == 'r')
	{
		TOKEN_DATA->type = Unknown;
		if (!line[1])
			ft_error_add(asm_data, ft_strjoin_orig("No value in reg ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else if (!ft_string_contain_only_num(&line[1]))
			ft_error_add(asm_data, ft_strjoin_orig("Detected Char in reg  ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else if (temp < 0 || temp > REG_NUMBER)
			ft_error_add(asm_data, ft_strjoin_orig("Wrong reg num ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else
			TOKEN_DATA->type = Register;
		return ;
	}
	ft_fill_token_command(asm_data, line);
}

void	ft_fill_token_direct(t_asm_data *asm_data, char *line)
{
	if (line[0] == DIRECT_CHAR)
	{
		ft_printf("token str = %s\n", TOKEN_DATA->str);
		if (line[1] == LABEL_CHAR)
			ft_fill_token_direct_labels(asm_data, &line[2]);
		else if (ft_isdigit(line[1]) || line[1] == '+' || line[1] == '-')
			ft_fill_token_direct_digits(asm_data, &line[1]);
		else if (line[1] == 'r')
			ft_fill_token_direct_regs(asm_data, &line[2]);
		else
		{
			TOKEN_DATA->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Unknown value in DIRECT_ADDR ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		}
		return ;
	}
	ft_fill_token_reg(asm_data, line, 0);
}

void	ft_fill_token_digits(t_asm_data *asm_data, char *line)
{
	if (ft_isdigit(line[0]) || line[0] == '+' || line[0] == '-')
	{
		TOKEN_DATA->type = Unknown;
		if (line[0] == '-')
			ft_error_add(asm_data, ft_strjoin_orig("Detected minus in number ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else if (ft_atol(line) > MEM_SIZE)
			ft_error_add(asm_data, ft_strjoin_orig("Value is greater than \
MEM_SIZE ", TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else if (!ft_string_contain_only_num(line))
			ft_error_add(asm_data, ft_strjoin_orig("Detected chars in number ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		else
			TOKEN_DATA->type = Number;
		return ;
	}
	ft_fill_token_direct(asm_data, line);
}

void	ft_fill_token(t_asm_data *asm_data, char *line)
{
	ft_printf("%s ", line);
	TOKEN_DATA->str = line;
	if (line[0] == ' ' || line[0] == '\t')
	{
		TOKEN_DATA->type = Whitespace;
		return ;
	}
	if (line[0] == SEPARATOR_CHAR)
	{
		TOKEN_DATA->type = Separator;
		return ;
	}
	if (ft_find_sym(line, LABEL_CHAR) && line[0] != DIRECT_CHAR)
	{
		if (ft_check_label_symbols(line))
			TOKEN_DATA->type = Label;
		else
		{
			TOKEN_DATA->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Wrong symbols in label ",\
			TOKEN_DATA->str), TOKEN_DATA->col, 1);
		}
		return ;
	}
	ft_fill_token_digits(asm_data, line);
}
