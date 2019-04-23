/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/23 15:46:06 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

int		main(int argc, char *argv[])
{
	t_vm		*vm;
	t_op		op_tab[17];

	vm = vm_new();
	args_read(argc, argv, vm);
	if (!vm->champion_count)
	{
		ft_printf("Count of champions must be between 2 and %d.\n", MAX_PLAYERS);
		exit(1);
	}
	vm->champion[vm->champion_count] = NULL;
	vm->winner = vm->champion[0];
	read_all_champs(vm->champion, vm->champion_count);
	vm_spread_champs(vm, vm->champion);
	introduce_players(vm->champion, vm->champion_count);
	init_optab(op_tab);
	while (!vm->end_game)
	{
		do_cyrcle(vm, op_tab);
		if (vm->cycles == vm->cycles_to_dump)
			vm_dump_memory(vm);
	}
	ft_printf("Winner is %s!\n", vm->winner->name);
	vm_delete(vm);
	return (0);
}
