/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:26:41 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/09 17:19:25 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	write_reg
**	Записывает значение value в память *memory по адрессу pos
**	Подразумевает, что value - значение регистра, поэтому
**	в память будет записано REG_SIZE байт.
*/

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

/*
**	st
**	Эта операция записывает значение из регистра, который был передан как 
**	первый параметр. А вот куда данная операция его записывает, зависит 
**	от типа второго аргумента:
**	
**	Аргумент #2 — T_REG
**	Если второй аргумент соответствует типу T_REG,
**	то значение записывается в регистр.
**	
**	Аргумент #2 — T_IND
**	Как мы помним аргументы типа T_IND это об относительных адресах.
**	Поэтому в данном случае порядок работы операции st такой:
**	Усечь значение второго аргумента по модулю IDX_MOD.
**	Определить адрес — текущая позиция + <ВТОРОЙ_АРГУМЕНТ> % IDX_MOD
**	Записать значение из регистра, который был передан в качестве 
**	первого аргумента, в память по полученному адресу.
*/

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

/*
**	sti
**	Эта операция записывает значение регистра, переданного 
**	в качестве первого параметра, по адресу — текущая позиция + 
**	(<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
*/
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
		{
			args[i] = get_indirect_addr(vm, (P_POS + 2 + ofs) % MEM_SIZE, P_POS);
			args[i] = get_4bytes(vm->memory, args[i]);
		}
		ofs += arg_type[i] == T_REG ? 1 : 2;
		i++;
	}
	write_reg(vm->memory, get_realtive_addr(P_POS, (args[1] + args[2]) % IDX_MOD), args[0]);
}
