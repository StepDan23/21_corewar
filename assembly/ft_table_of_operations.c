/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_of_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:59:19 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/17 20:56:38 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

int		g_command_nums[REG_NUMBER] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,\
	13, 14, 15, 16};

int		g_count_of_args[REG_NUMBER] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2,\
	3, 1, 1};

int		g_arg1_type[REG_NUMBER] = {
	T_DIR,
	T_DIR + T_IND,
	T_REG,
	T_REG,
	T_REG,
	T_REG + T_DIR + T_IND,
	T_REG + T_DIR + T_IND,
	T_REG + T_DIR + T_IND,
	T_DIR,
	T_REG + T_DIR + T_IND,
	T_REG,
	T_DIR,
	T_DIR + T_IND,
	T_REG + T_DIR + T_IND,
	T_DIR,
	T_REG
};

int		g_arg2_type[REG_NUMBER] = {
	0,
	T_REG,
	T_REG + T_IND,
	T_REG,
	T_REG,
	T_REG + T_DIR + T_IND,
	T_REG + T_DIR + T_IND,
	T_REG + T_DIR + T_IND,
	0,
	T_REG + T_DIR,
	T_REG + T_DIR + T_IND,
	0,
	T_REG,
	T_REG + T_DIR,
	0,
	0
};

int		g_arg3_type[REG_NUMBER] = {
	0,
	0,
	0,
	T_REG,
	T_REG,
	T_REG,
	T_REG,
	T_REG,
	0,
	T_REG,
	T_REG + T_DIR,
	0,
	0,
	T_REG,
	0,
	0
};

int		g_args_codes[REG_NUMBER] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

t_table_ops		*ft_table_operations_init(void)
{
	t_table_ops	*operations;

	operations = (t_table_ops *)malloc(sizeof(t_table_ops));
	if (!operations)
		exit(ft_printf("error in malloc ft_table_operations_init()\n"));
	operations->command_nums = g_command_nums;
	operations->count_of_args = g_count_of_args;
	operations->arg1_type = g_arg1_type;
	operations->arg2_type = g_arg2_type;
	operations->arg3_type = g_arg3_type;
	operations->args_codes = g_args_codes;
	return (operations);
}
