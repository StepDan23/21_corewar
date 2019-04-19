/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:11:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 17:25:50 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_token_type_value(t_types value)
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

int		ft_count_arg(int arg_type, int arg_num)
{
	int		res;

	res = 0;
	if (arg_type == 1)
		res = 1;
	if (arg_type == 10)
		res = 3;
	if (arg_type == 100)
		res = 5;
	if (arg_num == 1)
		res = res << 6;
	if (arg_num == 2)
		res = res << 4;
	if (arg_num == 3)
		res = res << 2;
	return (res);
}

void	ft_add_chain_in_list(t_asm_data *asm_data, t_list *what)
{
	if (!ASM_LABEL)
		ASM_LABEL = what;
	else
		ft_lstadd_last(ASM_LABEL, what);
}
