/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_performe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:26:48 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/06 02:47:16 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

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

void	init_f(void (*f[17])(t_vm *, t_proccess *))
{
	f[1] = &live;
	f[2] = &ld;
	f[3] = &st;
	f[4] = &add;
	f[5] = &sub;
	f[6] = &and;
	f[7] = &or;
	f[8] = &xor;
	f[9] = &zjmp;
	f[10] = &ldi;
	f[11] = &sti;
	f[12] = &ft_fork;
	f[13] = &lld;
	f[14] = &lldi;
	f[15] = &lfork;
}

void	performe_action(t_vm *vm, t_proccess *proccess, t_op op_tab[17])
{
	void (*f[17])(t_vm *, t_proccess *);

	init_f(f);
	ft_printf("Execute %s\n", op_tab[P_CT].name);
	if (op_tab[P_CT].coding_byte)
	{
		if (coding_byte_check(vm->memory[(P_POS + 1) % MEM_SIZE], op_tab[P_CT]))
		{
			if (has_register(vm->memory[(P_POS + 1) % MEM_SIZE]) &&\
				!valid_reg(vm->memory[(P_POS + 1) % MEM_SIZE], vm->memory, P_POS + 1, op_tab[P_CT]))
				P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
			else
			{
				f[P_CT](vm, proccess);
				P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
			}
		}
		else
			P_POS = get_new_pos(P_POS, op_tab[P_CT], vm->memory[(P_POS + 1) % MEM_SIZE]);
	}
	else
		f[P_CT](vm, proccess);
}

void	performe_proc(t_vm *vm, t_proccess *head, t_op op_tab[17])
{
	t_proccess	*proccess;

	proccess = head;
	while (proccess)
	{
		// ft_printf("Proccess %d now on %d\n", proccess->id, proccess->position);
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
