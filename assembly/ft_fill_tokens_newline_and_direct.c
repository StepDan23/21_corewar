/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tokens_newline_and_direct.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:42:54 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 19:40:44 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_add_new_str_token(t_asm_data *asm_data)
{
	t_token	*token;
	t_list	*chain;

	chain = ft_lstnew(NULL, sizeof(t_token));
	token = ft_token_init();
	chain->content = token;
	if (ASM_TOKENS == NULL)
		ASM_TOKENS = chain;
	else
		ft_lstadd_last(ASM_TOKENS, chain);
	token->row = ASM_NUM_ROW - 1;
	token->col = 0;
	token->str = "\n";
	token->type = Newline;
	MACHINE_NEW_LINE = 1;
}

void	ft_fill_token_direct_labels(t_asm_data *asm_data, char *line)
{
	ft_printf("dir labels = %s\n", line);
}

void	ft_fill_token_direct_digits(t_asm_data *asm_data, char *line)
{
	long long	temp;

	if (!ft_string_contain_only_num(line))
	{
		TOKEN_DATA->type = Unknown;
		ft_error_add(asm_data, ft_strjoin_orig("Chars in Direct value ",\
		TOKEN_DATA->str), TOKEN_DATA->col, 1);
		return ;
	}
	temp = ft_atol(line);
	if (temp < 0 || temp > MEM_SIZE)
	{
		TOKEN_DATA->type = Unknown;
		ft_error_add(asm_data, ft_strjoin_orig("Wrong value in Direct ",\
		TOKEN_DATA->str), TOKEN_DATA->col, 1);
	}
	else
		TOKEN_DATA->type = Direct;
}

void	ft_fill_token_direct_regs(t_asm_data *asm_data, char *line)
{
	long long	temp;

	TOKEN_DATA->type = Unknown;
	if (line[0] == 0)
	{
		ft_error_add(asm_data, ft_strjoin_orig("No value in Direct reg ",\
		TOKEN_DATA->str), TOKEN_DATA->col, 1);
		return ;
	}
	else if (!ft_string_contain_only_num(line))
	{
		ft_error_add(asm_data, ft_strjoin_orig("Chars in Direct value ",\
		TOKEN_DATA->str), TOKEN_DATA->col, 1);
		return ;
	}
	temp = ft_atol(line);
	if (temp < 0 || temp > REG_NUMBER)
		ft_error_add(asm_data, ft_strjoin_orig("Wrong value in Direct ",\
		TOKEN_DATA->str), TOKEN_DATA->col, 1);
	else
		TOKEN_DATA->type = Direct;
}
