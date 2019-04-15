/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:19:57 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/09 23:41:40 by artemiy          ###   ########.fr       */
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
	octets[3] =  memory[(pos + 3) % MEM_SIZE];
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
		return ((MEM_SIZE + (from + to) % MEM_SIZE));
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

/*
**	ld
**	Задача этой операции состоит в загрузке значения в регистр.
**	Но её поведение отличается в зависимости от типа первого аргумента:
**	
**	Аргумент #1 — T_DIR
**	Если тип первого аргумента это T_DIR, то число переданное в
**	качестве аргумента будет воспринято «как есть».
**	
**	Задачи операции:
**	
**	Записать полученное число в регистр, который был передан
**	в качестве второго аргумента.
**	
**	Если в регистр записали число 0, то установить значение carry в 1.
**	Если было записано не нулевое значение, то установить carry в 0.
**	
**	Аргумент #1 — T_IND
**	Если тип первого аргумента это T_IND, то в данном случае
**	число представляет собой адрес.
**	
**	В случае получения аргумента такого типа он
**	обрезается по модулю — <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
*/

void	ld(t_vm *vm, t_proccess *proccess)
{
	int				arg_type;
	int				number;
	int				index;

	arg_type = bit_extracted(vm->memory[(P_POS + 1) % MEM_SIZE], 2, 7);
	if (arg_type == T_DIR)
		index = (P_POS + 2) % MEM_SIZE;
	else
		index = get_indirect_addr(vm, (P_POS + 2) % MEM_SIZE, P_POS);
	number = get_4bytes(vm->memory, index);
	P_C = (number == 0 ? 1 : 0);
	if (arg_type == T_DIR)
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE] - 1] = number;
	else
		P_REG[vm->memory[(P_POS + 2 + 2) % MEM_SIZE] - 1] = number;
}

/*
**	lld
**	Данная операция ведет себя практически так же как и операция ld.
**	То есть записывает значение, полученное из первого аргумента,
**	в регистр, переданный как второй аргумент.
**	
**	Единственное различие между этими двумя операциями состоит в
**	применении усечения по модулю.
**	
**	Если первый аргумент имеет тип T_IND, то в этой операции мы
**	будем считывать 4 байта значения
**	по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>.
**	Не применяя усечение по модулю.
*/

void	lld(t_vm *vm, t_proccess *proccess)
{
	unsigned char	arg_octet;
	int				arg_type;
	int				number;
	int				index;

	arg_octet = vm->memory[(P_POS + 1) % MEM_SIZE];
	arg_type = bit_extracted(arg_octet, 2, 7);
	if (arg_type == T_DIR)
		index = (P_POS + 2) % MEM_SIZE;
	else
		index = get_indirect_laddr(vm, (P_POS + 2) % MEM_SIZE, P_POS);
	number = get_4bytes(vm->memory, index);
	P_C = (number == 0 ? 1 : 0);
	if (arg_type == T_DIR)
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE] - 1] = number;
	else
		P_REG[vm->memory[(P_POS + 2 + 2) % MEM_SIZE] - 1] = number;
}
