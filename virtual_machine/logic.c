/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:26:22 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/15 19:46:30 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	logic_arg_size
**	Возвращает размер аргумента для логических операций
*/

int		logic_arg_size(int arg_type)
{
	if (arg_type == T_DIR)
		return (4);
	else if (arg_type == T_REG)
		return (1);
	else
		return (2);
	return (0);
}

/*
**	and
**	Выполняет операцию «побитовое И» для значений первых двух аргументов
**	и записывает полученный результат в регистр, переданный в качестве
**	третьего аргумента.
**
**	Если записанный результат был равен нулю, то значение carry нужно
**	установить равным 1. Если результат был не нулевой, то — равным 0.
**
**	Поскольку первый и второй аргумент могут быть одного из трех типов,
**	мы рассмотрим как получить значение каждого из них:
**
**	Аргумент #1 / Аргумент #2 — T_REG
**	В данном случае значение берется из регистра, переданного
**	в качестве аргумента.
**
**	Аргумент #1 / Аргумент #2 — T_DIR
**	В этом случае используется переданное в качестве аргумента
**	числовое значение.
**
**	Аргумент #1 / Аргумент #2 — T_IND
**	Если тип аргумента T_IND, то необходимо установить адрес,
**	с которого будет считано 4 байта.
**	Адрес определяется следующим образом
**	текущая позиция + <АРГУМЕНТ> % IDX_MOD.
**	Считанное по этому адресу 4-байтовое число и будет требуемым значением.
*/

void	and(t_vm *vm, t_proccess *proccess)
{
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 2)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE],
									2, 7 - 2 * i);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
		{
			args[i] = get_indirect_addr(vm, (P_POS + 2 + ofs) % MEM_SIZE,
										P_POS);
			args[i] = get_4bytes(vm->memory, args[i]);
		}
		ofs += logic_arg_size(arg_type[i]);
		i++;
	}
	args[2] = vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1;
	P_REG[args[2]] = args[0] & args[1];
	P_C = P_REG[args[2]] ? 0 : 1;
}

/*
**	or
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на «побитовое ИЛИ».
*/

void	or(t_vm *vm, t_proccess *proccess)
{
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 2)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 2, 7 - 2 * i);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
		{
			args[i] = get_indirect_addr(vm, (P_POS + 2 + ofs) % MEM_SIZE, P_POS);
			args[i] = get_4bytes(vm->memory, args[i]);
		}
		ofs += logic_arg_size(arg_type[i]);
		i++;
	}
	args[2] = vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1;
	P_REG[args[2]] = args[0] | args[1];
	P_C = P_REG[args[2]] ? 0 : 1;
}

/*
**	xor
**	По своей сути эта операция полностью аналогична операции and.
**	Только в данном случае «побитовое И» заменяется на
**	«побитовое исключающее ИЛИ».
*/

void	xor(t_vm *vm, t_proccess *proccess)
{
	int		arg_type[3];
	int		args[3];
	int		i;
	int		ofs;

	i = 0;
	ofs = 0;
	while (i < 2)
	{
		arg_type[i] = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 2, 7 - 2 * i);
		if (arg_type[i] == T_REG)
			args[i] = P_REG[vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1];
		else if (arg_type[i] == T_DIR)
			args[i] = get_4bytes(vm->memory, (P_POS + 2 + ofs) % MEM_SIZE);
		else
		{
			args[i] = get_indirect_addr(vm, (P_POS + 2 + ofs) % MEM_SIZE, P_POS);
			args[i] = get_4bytes(vm->memory, args[i]);
		}
		ofs += logic_arg_size(arg_type[i]);
		i++;
	}
	args[2] = vm->memory[(P_POS + 2 + ofs) % MEM_SIZE] - 1;
	P_REG[args[2]] = args[0] ^ args[1];
	P_C = P_REG[args[2]] ? 0 : 1;
}

/*
**	zjmp
**	Эта та самая функция, на работу которой влияет значение флага carry.
**
**	Если оно равно 1, то функция обновляет значение PC
**	на адрес — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**
**	То есть zjmp устанавливает куда должна переместиться каретка
**	для выполнения следующей операции. Это позволяет нам
**	перепрыгивать в памяти на нужную позицию, а не выполнять всё по порядку.
**
**	Если значение carry равно нулю, перемещение не выполняется.
*/

void	zjmp(t_vm *vm, t_proccess *proccess)
{
	int	value;

	if (P_C)
	{
		value = get_2bytes(vm->memory, (P_POS + 1) % MEM_SIZE) % IDX_MOD;
		P_POS = get_realtive_addr(P_POS, value);
	}
	else
		P_POS = (P_POS + 3) % MEM_SIZE;
}
