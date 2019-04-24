/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:14:57 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/21 18:41:12 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	bit_extracted
**	Достает k бит с позиции p
**	Например bit_extracted(01101100, 2, 7) вернет 0b01 (1)
**	bit_extracted(01101100, 2, 5) вернет 0b10 (2)
*/

int		bit_extracted(int number, int k, int p)
{
	return (((1 << k) - 1) & (number >> (p - 1)));
}

/*
**	has_register
**	Проверяет байт кодирования аргументов на наличие регистра
**	octet - байт кодирования аргументов
*/

int		has_register(unsigned char octet)
{
	if (bit_extracted(octet, 2, 7) == T_REG)
		return (1);
	if (bit_extracted(octet, 2, 5) == T_REG)
		return (1);
	if (bit_extracted(octet, 2, 3) == T_REG)
		return (1);
	return (0);
}

/*
**	coding_byte_check
**	Проверяет байт кодирования аргументов на соответствие разрешенным
**	типам аргументов для данной операции
**	octet - байт кодирования аргументов
**	op - структура операции
*/

int		coding_byte_check(unsigned char octet, const t_op op)
{
	int				i;
	unsigned char	arg;

	i = 0;
	while (i < op.arg_num)
	{
		arg = bit_extracted(octet, 2, 7 - i * 2);
		if (arg == 3)
			arg = arg + 1;
		if (!(arg & op.arg_types[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
**	get_arg_size
**	Возвращает размер аргумента в в соответствии с типом операции
*/

int		get_arg_size(int arg_type, t_op op)
{
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == 3)
		return (2);
	else if (arg_type == T_DIR)
		return (op.is_short_dir ? 2 : 4);
	else
		return (0);
}

/*
**	valid_reg
**	Проверяет номер регистра, если номер > 16 или номер < 1
**	вернет 0.
**	octet - байт кодирования аргументов
**	memory - память виртуальной машины
**	op - структура операции
*/

int		valid_reg(unsigned char octet, unsigned char *memory, int pos, t_op op)
{
	int	i;
	int	tmp_pos;
	int	arg_type;

	i = 0;
	tmp_pos = (pos + 1) % MEM_SIZE;
	while (i < op.arg_num)
	{
		arg_type = bit_extracted(octet, 2, 7 - i * 2);
		if (arg_type == T_REG)
		{
			if (memory[tmp_pos] < 1 || memory[tmp_pos] > 16)
				return (0);
		}
		tmp_pos = (tmp_pos + get_arg_size(arg_type, op)) % MEM_SIZE;
		i++;
	}
	return (1);
}
