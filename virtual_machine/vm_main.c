/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/17 15:28:45 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

int		main(int argc, char *argv[])
{
	t_vm		*vm;
	t_op		op_tab[17];
	int			i;

	vm = vm_new();
	vm->champion[argc - 1] = NULL;
	i = 1;
	while (i < argc)
	{
		champions_add(argv[i], i, vm->champion);
		vm->p_total++;
		ft_printf("%s\n", vm->champion[i - 1]->filename);
		vm->p_num[vm->champion[i - 1]->id]++;
		i++;
	}
	vm->winner = vm->champion[0];
	read_all_champs(vm->champion);
	vm_spread_champs(vm, vm->champion);
	introduce_players(vm->champion);
	init_optab(op_tab);
	while (!vm->end_game)
	{
		do_cyrcle(vm, op_tab);
		if (!vm->cycles_to_dump)
			vm_dump_memory(vm->memory);
	}
	ft_printf("Winner is %s!\n", vm->winner->name);
	free(vm);
	return (0);
}
