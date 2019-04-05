/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_performe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:26:48 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/05 01:27:08 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

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

int		get_new_pos(int pos, t_op op, unsigned int octet)
{
	int	new_pos;
	int	i;
	int	arg;

	new_pos = pos + 1;
	if (op.coding_byte)
		new_pos += 1;
	i = 0;
	while (i < op.arg_num)
	{
		arg = bit_extracted(octet, 2, 7 - i * 2);
		new_pos += get_arg_size(arg, op);
		i++;
	}
	return (new_pos % MEM_SIZE);
}

void	set_new_op(t_vm *vm, t_proccess *proccess, t_op op_tab[17])
{
	P_CT = vm->memory[P_POS];
	if (P_CT < 17 && P_CT > 0)
		P_CTW = op_tab[P_CT].cycles_to_wait;
}

void	performe_action(t_vm *vm, t_proccess *proccess, t_op op_tab[17])
{
	if (op_tab[P_CT].coding_byte)
	{
		if (coding_byte_check(vm->memory[(P_POS + 1) % MEM_SIZE], op_tab[P_CT]))
		{
			if (has_register(vm->memory[(P_POS + 1) % MEM_SIZE]) &&\
				!valid_reg(vm->memory[(P_POS + 1) % MEM_SIZE], vm->memory, P_POS + 1, op_tab[P_CT]))
				P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
			else
				//Если все необходимые проверки были успешно пройдены, нужно выполнить операцию 
				P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
		}
		else
			P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
		// exit(0);
	}
	else
		//выполнить операцию и передвинуть каретку на следующую позицию.
		P_POS = get_new_pos(P_POS, op_tab[P_CT], 0);
		// exit(0);
}

void	performe_proc(t_vm *vm, t_proccess *head, t_op op_tab[17])
{
	t_proccess	*proccess;

	proccess = head;
	while (proccess)
	{
		ft_printf("Running %d\n", proccess->id);
		if (!P_CTW)
			set_new_op(vm, proccess, op_tab);
		if (P_CTW > 0)
			P_CTW--;
		if (!P_CTW)
		{
			if (P_CT < 17 && P_CT > 0)
				performe_action(vm, proccess, op_tab);
			else
				P_POS = (P_POS + 1) % MEM_SIZE;	
		}
		proccess = proccess->next;
	}
}
