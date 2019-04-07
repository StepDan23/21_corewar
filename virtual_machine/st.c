/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:26:41 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/08 02:11:29 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	write_reg(unsigned char *memory, int pos, unsigned int value)
{
	int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		memory[(pos + REG_SIZE - i - 1) % MEM_SIZE] = (value >> (i * 8));
		i++;
	}
}

void	st(t_vm *vm, t_proccess *proccess)
{
	int		arg_type;
	int		number;
	int		index;

	arg_type = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 2, 5);
	number = P_REG[vm->memory[(P_POS + 2) % MEM_SIZE] - 1];
	if (arg_type == T_REG)
		P_REG[vm->memory[(P_POS + 3) % MEM_SIZE] - 1] = number;
	else
	{
		index = get_indirect_addr(vm, (P_POS + 3) % MEM_SIZE, P_POS);
		write_reg(vm->memory, index, number);
	}
}

void	sti(t_vm *vm, t_proccess *proccess)
{
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 3)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 2, 7 - 2 * i);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1];
		else if (arg_type[i] == T_DIR)
			args[i] = get_2bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += arg_type[i] == T_REG ? 1 : 2;
		i++;
	}
	write_reg(vm->memory, get_realtive_addr(P_POS, (args[1] + args[2]) % IDX_MOD), args[0]);
}
