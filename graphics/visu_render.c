/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:36:36 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/22 12:10:18 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		render_status_img(t_window *window, t_vm *vm)
{
	SDL_Rect	dst;

	dst = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	FONT_CURR = FONT_PAUSE;
	if (WIN_STATUS == STAT_START)
	{
		SDL_RenderCopy(WIN_REND, BACK_START, NULL, &dst);
		print_str(window, "Press SPACE to start", 380, 820);
		print_str(window, "** Starting **", 1245, 40);
		print_start_names(window, vm);
	}
	else if (WIN_STATUS == STAT_PAUSE)
	{
		print_str(window, "Press SPACE to continue or S to step up", 178, 820);
		print_str(window, "** Paused **", 1258, 40);
	}
	else if (WIN_STATUS == STAT_END)
	{
		SDL_RenderCopy(WIN_REND, BACK_END, NULL, &dst);
		print_str(window, "CONGRATILATIONS TO", 364, 200);
		print_str(window, "Press ANY KEY to exit", 371, 820);
		print_str(window, vm->winner->name,
						609 - ft_strlen(vm->winner->name) * 12, 350);
		print_str(window, "** Finished **", 1245, 40);
	}
}

static void		render_status_val(t_window *window, t_vm *vm)
{
	int			height;
	int			i;

	i = 0;
	height = 80;
	FONT_CURR = FONT_STAT;
	FONT_COLOR = (SDL_Color){COL_WHITE};
	print_nbr(window, WIN_SPEED, 1459, height += 35);
	print_nbr(window, VM_CYCLE, 1287, height += 35);
	print_nbr(window, VM_P_TOTAL, 1324, height += 35);
	print_nbr(window, VM_CYCLE_TO_DIE, 1358, height += 35);
	print_nbr(window, CYCLE_DELTA, 1352, height += 35);
	print_nbr(window, NBR_LIVE, 1322, height += 35);
	print_nbr(window, MAX_CHECKS, 1352, height += 35);
	height = 380;
	while (VM_CHAMPS[i] != NULL)
	{
		print_nbr(window, VM_CHAMPS[i]->last_live, 1325, height += 60);
		print_nbr(window, VM_CHAMPS[i]->lives_in_period, 1435, height += 30);
		height += 30;
		i++;
	}
}

void			render_step(t_window *window, t_vm *vm, t_op op_tab[17])
{
	performe_proc(vm, vm->process, op_tab);
	render_carrier_source(window, vm);
	update_vm_state(vm);
render_tests(window, vm);
	FONT_CURR = FONT_PAUSE;
	FONT_COLOR = (SDL_Color){COL_WHITE};
	print_str(window, "Press SPACE to continue or S to step up", 178, 820);
	print_str(window, "** Paused **", 1258, 40);
	WIN_STATUS = STAT_PAUSE;
}

void			render_image(t_window *window, t_vm *vm, t_op op_tab[17])
{
	int		speed_cycle;

	speed_cycle = WIN_SPEED / 50;
	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
	SDL_RenderSetScale(WIN_REND, (WIN_WID / (float)SCREEN_WIDTH),
									(WIN_HEIG / (float)SCREEN_HEIGHT));
	render_carrier(window, vm);
	render_status_val(window, vm);
	if (WIN_STATUS == STAT_RUNN)
	{
		FONT_CURR = FONT_PAUSE;
		print_str(window, "** Running **", 1244, 40);
		while (speed_cycle >= 0)
		{
			performe_proc(vm, vm->process, op_tab);
			render_carrier_source(window, vm);
			update_vm_state(vm);
			speed_cycle--;
		}
	}
	else if (WIN_STATUS == STAT_STEP)
		render_step(window, vm, op_tab);
	else
		render_status_img(window, vm);
}
