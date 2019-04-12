/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:36:36 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/12 17:46:23 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		render_pause(t_window *window, t_champion *winner)
{
	SDL_Rect	dst;

	dst = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	if (WIN_STATUS == STAT_START)
	{
		SDL_RenderCopy(WIN_REND, BACK_PAUSE, NULL, &dst);
		print_str(window, "Press SPACE to start", 380, 800);
		print_str(window, "** Starting **", 1245, 40);
	}
	if (WIN_STATUS == STAT_PAUSE)
	{
		print_str(window, "Press SPACE to continue", 330, 800);
		print_str(window, "** Paused **", 1258, 40);
	}
	if (WIN_STATUS == STAT_END)
	{
		SDL_RenderCopy(WIN_REND, BACK_PAUSE, NULL, &dst);
		print_str(window, "Press ANY KEY to exit", 371, 800);
		print_str(window, winner->name, 604 - ft_strlen(winner->name) * 15, 550);
		print_str(window, "** Finished **", 1245, 40);
	}
}

static void		render_status(t_window *window, t_vm *vm)
{
	int			height;
	int			i;

	i = 0;
	height = 80;
	print_nbr(window, WIN_SPEED, 1459, height += 35);
	print_nbr(window, VM_CYCLE, 1287, height += 35);
	print_nbr(window, VM_P_TOTAL, 1324, height += 35);
	print_nbr(window, VM_CYCLE_TO_DIE, 1358, height += 35);
	print_nbr(window, CYC_DELTA, 1352, height += 35);
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

static void		change_run(t_window *window, t_vm *vm)
{
	static int	n;

	VM_CYCLE += WIN_SPEED / 50.0;
	if (VM_CYCLE_TO_DIE <= 0)
	{
		VM_WINNER = VM_CHAMPS[0];
		VM_CYCLE_TO_DIE = 0;
		WIN_STATUS = 3;
		return ;
	}
	if (VM_CYCLE >= 1460 * (n + 1))
	{
		n++;
		VM_CYCLE_TO_DIE -= CYC_DELTA;
	}
}

// static void		render_carrier(t_window *window)
// {
// 	SDL_Rect src = (SDL_Rect){0, 0, 100, 100};
// 	int	*pix;
// 	int pitch;
// 	SDL_LockTexture(WIN_BACK, &src, &pix, &pitch);
// 	ft_printf("%s", SDL_GetError());
// }

void			render_image(t_window *window, t_vm *vm)
{
	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
	SDL_RenderSetScale(WIN_REND, (WIN_WID / (float)SCREEN_WIDTH),
									(WIN_HEIG / (float)SCREEN_HEIGHT));
	FONT_CURR = FONT_STAT;
	render_status(window, vm);
	FONT_CURR = FONT_PAUSE;
	if (WIN_STATUS == STAT_START || WIN_STATUS == STAT_PAUSE
										|| WIN_STATUS == STAT_END)
		render_pause(window, VM_WINNER);
	else
	{
		print_str(window, "** Running **", 1244, 40);
		change_run(window, vm);
	}
	// render_carrier(window);
}
