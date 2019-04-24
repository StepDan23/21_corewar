/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:11:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 17:11:05 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_type_value(t_types value)
{
	int		res;

	res = 0;
	if (value == Register)
		res = T_REGS;
	else if (value == Direct_number || value == Direct_label)
		res = T_DIRS;
	else if (value == Number || value == Label_arg)
		res = T_INDS;
	return (res);
}

int		ft_cnt_arg(int arg_type, int arg_num, int flag)
{
	int		res;

	res = 0;
	if (arg_type == T_REGS)
		res = REG_CODE;
	if (arg_type == T_DIRS)
		res = DIR_CODE;
	if (arg_type == T_INDS)
		res = IND_CODE;
	if (arg_num == 1)
		res = res << 6;
	if (arg_num == 2)
		res = res << 4;
	if (arg_num == 3)
		res = res << 2;
	if (!flag)
		return (0);
	else
		return (res);
}

void	ft_add_chain_in_list(t_asm_data *asm_data, t_list *what)
{
	if (!ASM_LABEL)
		ASM_LABEL = what;
	else
		ft_lstadd_last(ASM_LABEL, what);
}

int		ft_solve_rows_2(t_syntax_row *row, int i, int counter)
{
	int		temp;

	temp = 0;
	if (ROW_ARG_CODE == 0 && counter == 192)
		temp = DIR_SIZE / ROW_T_DIR_COEF;
	else if ((ROW_ARG_CODE & counter) == (1 << (6 - 2 * i)))
		temp = 1;
	else if ((ROW_ARG_CODE & counter) == (2 << (6 - 2 * i)))
		temp = DIR_SIZE / ROW_T_DIR_COEF;
	else if ((ROW_ARG_CODE & counter) == (3 << (6 - 2 * i)))
		temp = 2;
	ROW_CODE_SIZE += temp;
	(temp) ? ROW_ARGS_SIZES[i++] = temp : 0;
	return (i);
}

void	ft_solve_rows_values(t_asm_data *asm_data, int i, int counter)
{
	t_list			*chain;
	t_syntax_row	*row;

	if (ERROR_SIZE > 0)
		return ;
	chain = ASM_SYNTAX_ROW;
	while (chain)
	{
		row = (t_syntax_row *)(chain->content);
		counter = 192;
		i = 0;
		while (counter > 0 && i < 3)
		{
			i = ft_solve_rows_2(row, i, counter);
			counter = counter >> 2;
		}
		chain = chain->next;
		ROW_CODE_SIZE += (ROW_ARG_CODE) ? 2 : 1;
		ROW_CODE_PLACE += ASM_CODE_SIZE;
		ASM_CODE_SIZE += ROW_CODE_SIZE;
	}
}
