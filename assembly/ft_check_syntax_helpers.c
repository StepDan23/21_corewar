/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:11:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 15:34:20 by lshanaha         ###   ########.fr       */
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
