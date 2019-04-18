/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/18 19:54:11 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

void	init_optab2(t_op op_tab[17])
{
	op_tab[9] = (t_op){"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1};
	op_tab[10] = (t_op){"ldi", 3, {T_REG | T_DIR | 3, T_DIR | T_REG, T_REG},
												10, 25, "load index", 1, 1};
	op_tab[11] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | 3, T_DIR | T_REG},
											11, 25, "store index", 1, 1};
	op_tab[12] = (t_op){"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1};
	op_tab[13] = (t_op){"lld", 2, {T_DIR | 3, T_REG, 0}, 13, 10,
													"long load", 1, 0};
	op_tab[14] = (t_op){"lldi", 3, {T_REG | T_DIR | 3, T_DIR | T_REG, T_REG},
											14, 50, "long load index", 1, 1};
	op_tab[15] = (t_op){"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork",
																		0, 1};
	op_tab[16] = (t_op){"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0};
	op_tab[0] = (t_op){0, 0, {0}, 0, 0, 0, 0, 0};
}

void	init_optab(t_op op_tab[17])
{
	op_tab[1] = (t_op){"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0};
	op_tab[2] = (t_op){"ld", 2, {T_DIR | 3, T_REG, 0}, 2, 5, "load", 1, 0};
	op_tab[3] = (t_op){"st", 2, {T_REG, 3 | T_REG, 0}, 3, 5, "store", 1, 0};
	op_tab[4] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1,
																		0};
	op_tab[5] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction",
																		1, 0};
	op_tab[6] = (t_op){"and", 3, {T_REG | T_DIR | 3, T_REG | 3 | T_DIR, T_REG},
							6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	op_tab[7] = (t_op){"or", 3, {T_REG | 3 | T_DIR, T_REG | 3 | T_DIR, T_REG},
						7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	op_tab[8] = (t_op){"xor", 3, {T_REG | 3 | T_DIR, T_REG | 3 | T_DIR, T_REG},
							8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	init_optab2(op_tab);
}

void	introduce_players(t_champion **players)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (players[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
		players[i]->id, players[i]->size, players[i]->name,
								players[i]->comment);
		i++;
	}
}

void	update_vm_state(t_vm *vm)
{
	if (!vm->cycles_to_die)
	{
		proccess_check_live(vm, &vm->process);
		if (vm->live_exec >= NBR_LIVE || vm->checkups >= MAX_CHECKS)
		{
			vm->cycles_die -= CYCLE_DELTA;
			vm->checkups = 0;
			if (vm->cycles_die <= 0)
				vm->end_game = 1;
		}
		else
			vm->checkups++;
		vm->cycles_to_die = vm->cycles_die;
		vm->live_exec = 0;
	}
	vm->cycles++;
	vm->cycles_to_die--;
}

void	do_cyrcle(t_vm *vm, t_op op_tab[17])
{
	performe_proc(vm, vm->process, op_tab);
	update_vm_state(vm);
}

t_vm	*init_vm_test(int argc, char *argv[])
{
	t_vm		*vm;
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
		vm->champion_count++;
		i++;
	}
	vm->winner = vm->champion[0];
	read_all_champs(vm->champion);
	vm_spread_champs(vm, vm->champion);
	return (vm);
}
