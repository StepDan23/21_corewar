/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_performe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:26:48 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/24 15:14:42 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

/*
**	get_new_pos
**	Вызывается для процесса после выполнения операции
**	Перемещает каретку на новую позицию
*/

int		get_new_pos(int pos, t_op op, unsigned int octet)
{
	int	new_pos;
	int	i;
	int	arg;

	new_pos = pos + 1;
	if (op.coding_byte)
	{
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
	i = 0;
	while (i < op.arg_num)
	{
		new_pos += get_arg_size(op.arg_types[i], op);
		i++;
	}
	return (new_pos % MEM_SIZE);
}

/*
**	set_new_op
**	Вызывается для процесса, если cyrcles_to_wait = 0
**	Устанавливает процессу номер операции
*/

void	set_new_op(t_vm *vm, t_proccess *proccess, t_op op_tab[17])
{
	int		valid_op_code;

	P_CT = vm->memory[P_POS];
	valid_op_code = P_CT < 17 && P_CT > 0;
	if (valid_op_code)
		P_CTW = op_tab[P_CT].cycles_to_wait;
	else
		P_CTW = 0;
}

/*
**	init_f
**	Инициализация массива функций-опрераций
*/

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
	f[16] = &aff;
}

/*
**	performe_action
**	Вызывается для процесса, если cyrcles_to_wait = 0 и
**	номер операции корректный.
**	Проверяет правильность байта кодирования аргументов (если есть)
**	Выполняет операцию и перемещает каретку на новую позицию
*/

void	performe_action(t_vm *vm, t_proccess *proccess, t_op op_tab[17],
						void (*f[17])(t_vm *, t_proccess *))
{
	unsigned int	arg_types;
	t_op			op;

	op = op_tab[P_CT];
	if (op.coding_byte)
	{
		arg_types = VM_M[(P_POS + 1) % MEM_SIZE];
		if (coding_byte_check(arg_types, op))
		{
			if (has_register(arg_types) &&\
				!valid_reg(arg_types, VM_M, P_POS + 1, op))
				P_POS = get_new_pos(P_POS, op, arg_types);
			else
			{
				f[P_CT](vm, proccess);
				P_POS = get_new_pos(P_POS, op, arg_types);
			}
		}
		else
			P_POS = get_new_pos(P_POS, op, arg_types);
	}
	else
		f[P_CT](vm, proccess);
}

/*
**	performe_proc
**	Вызывается каждый цикл.
**	Итерируется по всем живым процессам и выполняет необходимые действия
*/

void	performe_proc(t_vm *vm, t_proccess *head, t_op op_tab[17])
{
	t_proccess	*proccess;
	void		(*f[17])(t_vm *, t_proccess *);

	proccess = head;
	init_f(f);
	while (proccess)
	{
		if (!P_CTW)
			set_new_op(vm, proccess, op_tab);
		if (P_CTW > 0)
			P_CTW--;
		if (!P_CTW && P_CT < 17 && P_CT > 0)
		{
			proccess->pos_written = -1;
			performe_action(vm, proccess, op_tab, f);
		}
		else if (!P_CTW)
		{
			proccess->pos_written = -1;
			P_POS = (P_POS + 1) % MEM_SIZE;
		}
		proccess = proccess->next;
	}
}
