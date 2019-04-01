/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:36:30 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/01 23:00:55 by artemiy          ###   ########.fr       */
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

t_vm	*vm_new(int dump)
{
	t_vm	*vm;

	vm = (t_vm *)malloc(sizeof(t_vm));
	if (!vm)
		exit(2);
	vm->cycles = 0;
	vm->champion = NULL;
	vm->process = NULL;
	vm->cycles_die = CYCLE_TO_DIE;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->cycles_to_dump = dump;
	vm->dump = dump;
	vm_init_memory(vm->memory);
	return (vm);
}

void	vm_load_champ(t_vm *vm, t_champion *champ, int index)
{
	unsigned int	i;

	i = 0;
	while (i < champ->size)
	{
		vm->memory[index + i] = champ->code[i];
		i++;
	}
}

void	vm_dump_memory(unsigned char *memory)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02hhx ", memory[i]);
		if ((i + 1) % 32 == 0 && i)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}
