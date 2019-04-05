/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:30:26 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/05 22:57:26 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ldi(t_vm *vm, t_proccess *proccess)
{
	int		index;
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
			args[i] = get_2bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
			args[i] = get_4bytes(vm->memory, (get_2bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += arg_type[i] == T_REG ? 1 : 2;
		i++;
	}
	P_REG[args[2]] = get_4bytes(vm->memory, (P_POS + (args[0] + args[1]) % IDX_MOD) % MEM_SIZE);
}
