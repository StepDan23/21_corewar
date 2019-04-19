/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:11:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 20:55:15 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_type_value(t_types value)
{
	int		res;

	if (value == Register)
		res = T_REGS;
	else if (value == Direct_number || value == Direct_label)
		res = T_DIRS;
	else if (value == Number || value == Label_arg)
		res = T_INDS;
	else
		ft_printf("Strange type of arg = %d\n", value);
	return (res);
}

int		ft_cnt_arg(int arg_type, int arg_num, int flag)
{
	int		res;

	res = 0;
	if (arg_type == T_REGS)
		res = 1;
	if (arg_type == T_DIRS)
		res = 2;
	if (arg_type == T_INDS)
		res = 3;
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
