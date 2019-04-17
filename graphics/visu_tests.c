/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:52:21 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/17 12:09:20 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void			render_tests(t_window *window, t_vm *vm)
{
	t_proccess	*carriers;
	int			count;

	carriers = vm->process;
	count = 0;
	ft_printf("****************** start carier info: **********************\n");
	ft_printf("vm_champs = %d\n", VM_CHAMP_COUNT);
	ft_printf("speed = %d\n", WIN_SPEED / 50);
	while (carriers)
	{
		ft_printf("__________________________________________________\n");
		ft_printf("carier info: player_id = %d position = %d cycles_wait = %d \n",
					carriers->player_id, carriers->position, carriers->cycles_to_wait);
		ft_printf("pos_written = %d\n", carriers->pos_written);
		if (carriers->pos_written >= 0)
			ft_printf("code_to_written = %d%d %d%d %d%d %d%d\n",
			VM_MEMORY[carriers->pos_written] / 16, VM_MEMORY[carriers->pos_written] % 16,
			VM_MEMORY[carriers->pos_written + 1] / 16, VM_MEMORY[carriers->pos_written + 1] % 16,
			VM_MEMORY[carriers->pos_written + 2] / 16, VM_MEMORY[carriers->pos_written + 2] % 16,
			VM_MEMORY[carriers->pos_written + 3] / 16, VM_MEMORY[carriers->pos_written + 3] % 16);
		carriers = carriers->next;
		count++;
		ft_printf("__________________________________________________\n");
	}
	ft_printf("processes count = %d\n", count);
	ft_printf("****************** end carier info: **********************\n");
}

void			init_tests(t_vm *vm)
{
	t_proccess	*carriers;

	carriers = vm->process;
	ft_printf("******************************************\n");
	ft_printf("vm_champs = %d\n", VM_CHAMP_COUNT);
	while (carriers)
	{
		ft_printf("players carrier = %d\n", carriers->player_id);
		carriers = carriers->next;
	}
}
