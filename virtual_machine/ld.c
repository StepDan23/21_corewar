/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:19:57 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/06 02:42:32 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_4bytes(unsigned char *memory, int pos)
{
	int				total;
	unsigned char	octets[4];

	octets[0] = memory[pos] << 24;
	octets[1] = memory[(pos + 1) % MEM_SIZE] << 16;
	octets[2] = memory[(pos + 2) % MEM_SIZE] << 8;
	octets[3] =  memory[(pos + 3) % MEM_SIZE];
	total = octets[0] | octets[1] | octets[2] | octets[3];
	return ((unsigned int)total);
}

int		get_2bytes(unsigned char *memory, int pos)
{
	int				total;
	unsigned char	octets[2];

	octets[0] = memory[pos] << 8;
	octets[1] = memory[(pos + 1) % MEM_SIZE];
	total = octets[0] | octets[1];
	return ((short)total);
}
#include "libft.h"
void	ld(t_vm *vm, t_proccess *proccess)
{
	unsigned char	arg_octet;
	int				arg_type;
	int				number;
	int				index;

	arg_octet = vm->memory[(P_POS + 1) % MEM_SIZE];
	arg_type = bit_extracted(arg_octet, 7, 2);
	if (arg_type == T_DIR)
		index = (P_POS + 2) % MEM_SIZE;
	else
		index = (P_POS + get_2bytes(vm->memory, (P_POS + 2) % MEM_SIZE) % IDX_MOD) % MEM_SIZE;
	number = get_4bytes(vm->memory, index % MEM_SIZE);
	P_C = (number == 0 ? 1 : 0);
	if (arg_type == T_DIR)
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE]] = number;
	else
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE]] = number;
}

void	lld(t_vm *vm, t_proccess *proccess)
{
	unsigned char	arg_octet;
	int				arg_type;
	int				number;
	int				index;

	arg_octet = vm->memory[(P_POS + 1) % MEM_SIZE];
	arg_type = bit_extracted(arg_octet, 7, 2);
	if (arg_type == T_DIR)
		index = (P_POS + 2) % MEM_SIZE;
	else
		index = (P_POS + get_2bytes(vm->memory, (P_POS + 2) % MEM_SIZE)) % MEM_SIZE;
	number = get_4bytes(vm->memory, index % MEM_SIZE);
	P_C = (number == 0 ? 1 : 0);
	if (arg_type == T_DIR)
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE]] = number;
	else
		P_REG[vm->memory[(P_POS + 2 + 4) % MEM_SIZE]] = number;
}
