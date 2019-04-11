/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:36:36 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/11 14:10:21 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		render_pause(t_window *window, t_player **players)
{
	SDL_Rect	dst;

	dst = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	if (WIN_STATUS == 0)
	{
		SDL_RenderCopy(WIN_REND, BACK_PAUSE, NULL, &dst);
		print_str(window, "Press SPACE to start", 380, 800);
		print_str(window, "** Starting **", 1245, 40);
	}
	if (WIN_STATUS == 2)
	{
		print_str(window, "Press SPACE to continue", 330, 800);
		print_str(window, "** Paused **", 1258, 40);
	}
	if (WIN_STATUS == 3)
	{
		SDL_RenderCopy(WIN_REND, BACK_PAUSE, NULL, &dst);
		print_str(window, "Press ANY KEY to exit", 371, 800);
		print_str(window, players[0]->name, 600 - ft_strlen(players[0]->name) * 10.5, 550);
		print_str(window, "** Finished **", 1245, 40);
	}
}

static void		render_status(t_window *window, t_run *running, t_player **players)
{
	int			height;
	int			i;

	i = 0;
	height = 80;
	print_nbr(window, RUN_SPEED, 1459, height += 35);
	print_nbr(window, (int)RUN_CYCLE, 1287, height += 35);
	print_nbr(window, RUN_PROC, 1324, height += 35);
	print_nbr(window, CYC_DIE, 1358, height += 35);
	print_nbr(window, CYC_DELTA, 1352, height += 35);
	print_nbr(window, NBR_LIVE, 1322, height += 35);
	print_nbr(window, MAX_CHECKS, 1352, height += 35);
	height = 380;
	while (players[i] != NULL)
	{
		print_nbr(window, players[i]->last_live, 1325, height += 60);
		print_nbr(window, players[i]->lives_in_period, 1435, height += 30);
		height += 30;
		i++;
	}
}

static void		change_run(t_window *window, t_run *running)
{
	static int	n;

	RUN_CYCLE += RUN_SPEED / 50.0;
	if (CYC_DIE <= 0)
	{
		CYC_DIE = 0;
		WIN_STATUS = 3;
		return ;
	}
	if (RUN_CYCLE >= 1460 * (n + 1))
	{
		n++;
		CYC_DIE -= CYC_DELTA;
	}
}

void			render_image(t_window *window, t_run *running, t_player **players)
{

	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
	SDL_RenderSetScale(WIN_REND, (WIN_WID / (float)SCREEN_WIDTH),
									(WIN_HEIG / (float)SCREEN_HEIGHT));
	FONT_CURR = FONT_STAT;
	render_status(window, running, players);
	FONT_CURR = FONT_PAUSE;
	if (WIN_STATUS == 0 || WIN_STATUS == 2 || WIN_STATUS == 3)
		render_pause(window, players);
	else
	{
		print_str(window, "** Running **", 1244, 40);
		change_run(window, running);
	}
}
