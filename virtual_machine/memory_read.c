/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:54:21 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/18 19:54:11 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Считывает 4 байта памяти и возвращает знаковое число
*/

int		get_4bytes(unsigned char *memory, int pos)
{
	int	total;
	int	octets[4];

	octets[0] = memory[pos] << 24;
	octets[1] = memory[(pos + 1) % MEM_SIZE] << 16;
	octets[2] = memory[(pos + 2) % MEM_SIZE] << 8;
	octets[3] = memory[(pos + 3) % MEM_SIZE];
	total = octets[0] | octets[1] | octets[2] | octets[3];
	return (total);
}

/*
**	Считывает 2 байта памяти и возвращает знаковое число
*/

int		get_2bytes(unsigned char *memory, int pos)
{
	short	total;
	int		octets[2];

	octets[0] = memory[pos];
	octets[1] = memory[(pos + 1) % MEM_SIZE];
	total = (octets[0] << 8) | octets[1];
	return ((short)total);
}

/*
**	get_realtive_addr
**	Расчитывает адресс (индекс) в памяти относительно параметра from
**	Учитывает цикличность памяти.
**	from - адресс (индекс) от куда откладывается to
**	to - число на сколько байт вперед (to > 0) или назад (to < 0)
**	находится искомый адресс
*/

int		get_realtive_addr(int from, int to)
{
	if (from + to < 0)
	{
		if ((from + to) % MEM_SIZE)
			return ((MEM_SIZE + (from + to) % MEM_SIZE));
		else
			return (0);
	}
	else
		return ((from + to) % MEM_SIZE);
}

/*
**	get_indirect_addr
**	Cчитывает адресс, записаный в памяти по индексу pos,
**	делает усечение по IDX_MOD.
**	Возвращает индекс from + pos
**	Учитывает цикличность памяти.
**	pos - индекс памяти, в котором записано число
**	на сколько байт вперед (to > 0) или назад (to < 0)
**	from - адресс (индекс) от куда откладывается to
**	vm - виртуальная машина
*/

int		get_indirect_addr(t_vm *vm, int pos, int from)
{
	int	index;

	index = get_2bytes(vm->memory, pos) % IDX_MOD;
	return (get_realtive_addr(from, index));
}

/*
**	get_indirect_laddr
**	Делает то же самое, что и get_indirect_addr, но без усечения по модулю.
*/

int		get_indirect_laddr(t_vm *vm, int pos, int from)
{
	int	ind;

	ind = get_2bytes(vm->memory, pos);
	return (get_realtive_addr(from, ind));
}
