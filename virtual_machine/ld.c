/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:19:57 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/08 01:58:53 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

int		get_2bytes(unsigned char *memory, int pos)
{
	int	total;
	int	octets[2];

	octets[0] = memory[pos];
	octets[1] = memory[(pos + 1) % MEM_SIZE];
	total = (octets[0] << 8) | octets[1];
	return ((short)total);
}

int		get_realtive_addr(int from, int to)
{
	if (from + to < 0)
		return ((MEM_SIZE + (from + to) % MEM_SIZE));
	else
		return ((from + to) % MEM_SIZE);
}

int		get_indirect_addr(t_vm *vm, int pos, int from)
{
	int	ind;

	ind = get_2bytes(vm->memory, pos) % IDX_MOD;
	return (get_realtive_addr(from, ind));
}

int		get_indirect_laddr(t_vm *vm, int pos, int from)
{
	int	ind;

	ind = get_2bytes(vm->memory, pos);
	return (get_realtive_addr(from, ind));
}

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

#include "libft.h"

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
