/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 02:04:29 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/06 02:09:06 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add(t_vm *vm, t_proccess *proccess)
{
	int		left;
	int		right;
	int		target;
	
	left = P_REG[vm->memory[(P_POS + 2) % MEM_SIZE]];
	right = P_REG[vm->memory[(P_POS + 3) % MEM_SIZE]];
	target = vm->memory[(P_POS + 4) % MEM_SIZE];
	P_REG[target] = left + right;
	if (left + right == 0)
		P_C = 1;
	else
		P_C = 0;
}

void	sub(t_vm *vm, t_proccess *proccess)
{
	int		left;
	int		right;
	int		target;
	
	left = P_REG[vm->memory[(P_POS + 2) % MEM_SIZE]];
	right = P_REG[vm->memory[(P_POS + 3) % MEM_SIZE]];
	target = vm->memory[(P_POS + 4) % MEM_SIZE];
	P_REG[target] = left - right;
	if (left - right == 0)
		P_C = 1;
	else
		P_C = 0;
}