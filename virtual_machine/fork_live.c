/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:39:26 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/06 02:46:28 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_fork(t_vm *vm, t_proccess *proccess)
{
	int	index;
	int	i;

	index = get_2bytes(vm->memory,(P_POS + 1) % MEM_SIZE) % IDX_MOD;
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, (P_POS + index) % MEM_SIZE));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	P_POS = (P_POS + 2) % MEM_SIZE;
}

void	lfork(t_vm *vm, t_proccess *proccess)
{
	int	index;
	int	i;

	index = get_2bytes(vm->memory,(P_POS + 1) % MEM_SIZE);
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, (P_POS + index) % MEM_SIZE));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	P_POS = (P_POS + 2) % MEM_SIZE;
}

void	live(t_vm *vm, t_proccess *proccess)
{
	int			number;
	t_champion	*player;

	number = get_4bytes(vm->memory, (P_POS + 1) % MEM_SIZE);
	proccess->is_live = 1;
	vm->live_exec++;
	player = vm->champion;
	while (player)
	{
		if (player->id == -number)
			vm->winner = player;
		player = player->next;
	}
	P_POS = (P_POS + 4) % MEM_SIZE;
}

