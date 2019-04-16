/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:52:21 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/16 21:30:57 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void			render_tests(t_window *window, t_vm *vm)
{
	t_proccess	*carriers;
	int			count;

	carriers = vm->process;
	count = 0;
	ft_printf("******************************************\n");
	ft_printf("vm_champs = %d\n", VM_CHAMP_COUNT);
	ft_printf("speed = %d\n", WIN_SPEED / 50);
	while (carriers)
	{
		ft_printf("players carrier = %d position = %d cycles_wait = %d \n"
			, carriers->player_id, carriers->position,
									carriers->cycles_to_wait);
		carriers = carriers->next;
		count++;
	}
	ft_printf("processes count = %d\n", count);
	ft_printf("******************************************\n");
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
