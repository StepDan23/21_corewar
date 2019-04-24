/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:36:30 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/24 16:57:15 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

void	vm_init_memory(unsigned char *memory)
{
	unsigned int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		memory[i] = 0;
		i++;
	}
}

t_vm	*vm_new(void)
{
	t_vm	*vm;
	int		i;

	vm = (t_vm *)malloc(sizeof(t_vm));
	if (!vm)
		exit(2);
	vm->cycles = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->champion[i] = NULL;
		i++;
	}
	vm->process = NULL;
	vm->cycles_die = CYCLE_TO_DIE;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles_to_dump = -1;
	vm->live_exec = 0;
	vm->checkups = 1;
	vm->p_total = 0;
	vm->champion_count = 0;
	vm->end_game = 0;
	vm->bit_flags = 1;
	vm_init_memory(vm->memory);
	return (vm);
}

void	vm_delete(t_vm *vm)
{
	int			i;
	t_proccess	*curr;
	t_proccess	*next;

	if (vm == NULL)
		return ;
	i = 0;
	while (i < vm->champion_count)
	{
		if (vm->champion[i]->code)
			free(vm->champion[i]->code);
		free(vm->champion[i]);
		i++;
	}
	curr = vm->process;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(vm);
}

void	vm_dump_memory(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02hhx ", vm->memory[i]);
		if ((i + 1) % 32 == 0 && i)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
	vm_delete(vm);
	exit(0);
}
