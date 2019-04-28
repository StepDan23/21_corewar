/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/25 13:55:41 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

void	introduce_players(t_champion **players, int count)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
		players[i]->id, players[i]->size, players[i]->name,
								players[i]->comment);
		i++;
	}
}

void	do_cyrcle(t_vm *vm, t_op op_tab[17])
{
	performe_proc(vm, vm->process, op_tab);
	update_vm_state(vm);
}

int		main(int argc, char *argv[])
{
	t_vm		*vm;
	t_op		op_tab[17];

	vm = init_vm_test(argc, argv);
	introduce_players(vm->champion, vm->champion_count);
	init_optab(op_tab);
	while (!vm->end_game)
	{
		do_cyrcle(vm, op_tab);
		if (vm->cycles == vm->cycles_to_dump)
			vm_dump_memory(vm);
	}
	ft_printf("Player %d (%s) won\n", vm->winner->id, vm->winner->name);
	vm_delete(vm);
	return (0);
}
