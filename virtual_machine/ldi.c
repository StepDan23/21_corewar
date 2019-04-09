/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:30:26 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/09 17:13:01 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	ldi
** Данная операция записывает значение в регистр, 
** который был ей передан как третий параметр. 
** Значением, которая она записывает, являются 4 байта. 
** Эти 4 байта она считывает по адресу, который формируется 
** по следующему принципу:текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> +
**  									<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>) % IDX_MOD.
** 
** Поскольку операция может принимать разные типы первого и второго аргументов,
** рассмотрим способ получения значения для каждого типа:
** 
** Аргумент #1 / Аргумент #2 — T_REG
** Значение содержится в регистре, который был передан в качестве параметра.
** 
** Аргумент #1 / Аргумент #2 — T_DIR
** В данном случае у нас аргумент уже содержит свое значение.
** 
** Аргумент #1 — T_IND
** Чтобы получить значение этого аргумента, нужно считать 4 байта по адресу
** текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
*/

void	ldi(t_vm *vm, t_proccess *proccess)
{
	int		num;
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
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += arg_type[i] == T_REG ? 1 : 2;
		i++;
	}
	num = get_4bytes(vm->memory, (P_POS + (args[0] + args[1]) % IDX_MOD) % MEM_SIZE);
	P_REG[args[2]] = num;
}

/*
**	lldi
**	По своей сути данная операция аналогична операции ldi.
**	
**	Она записывает значение в регистр, который был передан ей как третий параметр. 
**	Значением, которая эта операция записывает, являются считанные 4 байта.
**	
**	Они считываются по адресу, который формируется по следующему принципу: 
**	текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>).
**	
**	В отличие от операции ldi в этом случае при формировании адреса
**	не нужно делать усечение по модулю IDX_MOD.
*/

void	lldi(t_vm *vm, t_proccess *proccess)
{
	int		num;
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
			args[i] = get_4bytes(vm->memory, (P_POS + get_2bytes(vm->memory,\
						(P_POS + 2 + ofs) % MEM_SIZE) % IDX_MOD) % MEM_SIZE);
		ofs += arg_type[i] == T_REG ? 1 : 2;
		i++;
	}
	num = get_4bytes(vm->memory, (P_POS + (args[0] + args[1]) % IDX_MOD) % MEM_SIZE);
	P_REG[args[2]] = num;
	P_C = num ? 0 : 1;
}
