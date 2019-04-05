/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:14:57 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/05 20:15:34 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		bit_extracted(int number, int k, int p) 
{ 
	return (((1 << k) - 1) & (number >> (p - 1))); 
} 

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

int		coding_byte_check(unsigned char octet, const t_op op)
{
	int				i;
	unsigned char	arg;

	i = 0;
	while (i < op.arg_num)
	{
		arg = bit_extracted(octet, 2, 7 - i * 2);
		if (!(arg & op.arg_types[i]))
			return (0);
		i++;
	}
	return (1);
}

int		get_arg_size(int arg_type, t_op op)
{
	if (arg_type == T_REG)
		return (1);
	else if (arg_type == T_IND)
		return (2);
	else if (arg_type == T_DIR)
		return (op.is_short_dir ? 2 : 4);
	else
		return (0);
}

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
