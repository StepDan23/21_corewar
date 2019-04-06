/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:26:22 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/06 01:38:52 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		and_arg_size(int arg_type)
{
	if (arg_type == T_DIR)
		return (4);
	else if (arg_type == T_REG)
		return (1);
	else if (arg_type == T_IND)
		return (2);
	return (0);
}

void	and(t_vm *vm, t_proccess *proccess)
{
	int		res;
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 3)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 7 - 2 * i, 2);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE]];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += and_arg_size(arg_type[i]);
		i++;
	}
	res = args[0] & args[1];
	P_REG[args[2]] = res;
	P_C = res ? 0 : 1;
}

void	or(t_vm *vm, t_proccess *proccess)
{
	int		res;
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 3)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 7 - 2 * i, 2);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE]];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += and_arg_size(arg_type[i]);
		i++;
	}
	res = args[0] | args[1];
	P_REG[args[2]] = res;
	P_C = res ? 0 : 1;
}

void	xor(t_vm *vm, t_proccess *proccess)
{
	int		res;
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 3)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 7 - 2 * i, 2);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE]];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += and_arg_size(arg_type[i]);
		i++;
	}
	res = args[0] ^ args[1];
	P_REG[args[2]] = res;
	P_C = res ? 0 : 1;
}

void	zjmp(t_vm *vm, t_proccess *proccess)
{
	int		index;

	if (P_C)
	{
		index = get_2bytes(vm->memory, (P_POS + 1) % MEM_SIZE) % IDX_MOD;
		P_POS = index;
	}
	else
		P_POS = (P_POS + 2) % MEM_SIZE;
}
