/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/09 13:14:10 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		visu_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	// if (WIN_BACK != NULL)
	// 	SDL_DestroyTexture(WIN_BACK);
	if (FONT_PAUSE != NULL)
		TTF_CloseFont(FONT_PAUSE);
	SDL_DestroyWindow(WIN_WIN);
	FONT_STAT = NULL;
	FONT_PAUSE = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	// IMG_Quit();
	SDL_Quit();
	// exit(1);
}

static void		render_pause(t_window *window)
{
	SDL_Rect	dst;

	if (WIN_STATUS == 0)
	{
		dst = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
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
		print_str(window, "Press ANY KEY to exit", 330, 800);
		print_str(window, "** Finished **", 1245, 40);
	}
}

static void		change_run(t_window *window, t_run *running)
{
	RUN_CYCLE++;
	RUN_TMP++;
	if (CYC_DIE <= 0)
	{
		CYC_DIE = 0;
		WIN_STATUS = 3;
		return ;
	}
	if (RUN_TMP == CYC_DIE)
	{
		RUN_TMP -= CYC_DIE;
		CYC_DIE -= CYC_DELTA;
	}
}

static void		render_running(t_window *window, t_run *running)
{
	print_str(window, "** Running **", 1244, 40);
	change_run(window, running);
}

static t_run	*init_running(void)
{
	t_run		*running;

	running = (t_run*)malloc(sizeof(t_run));
	RUN_SPEED = 50;
	RUN_CYCLE = 0;
	RUN_PROC = 2;
	CYC_DIE = 1460;
	CYC_DELTA = 50;
	NBR_LIVE = 21;
	MAX_CHECKS = 10;
	return (running);
}

int				main(void)
{
	t_window	*window;
	t_run		*running;

	if (!(window = init_win()))
		return (0);
	if (load_files(window) != 0)
		WIN_QUIT = 1;
	if (!(running = init_running()))
		WIN_QUIT = 1;
	while (!WIN_QUIT)
	{
		SDL_RenderClear(WIN_REND);
		win_events(window);
		SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
		SDL_RenderSetScale(WIN_REND, (WIN_WID / (float)SCREEN_WIDTH),
										(WIN_HEIG / (float)SCREEN_HEIGHT));
		if (WIN_STATUS == 0 || WIN_STATUS == 2 || WIN_STATUS == 3)
			render_pause(window);
		else
			render_running(window, running);
		SDL_RenderPresent(WIN_REND);
		SDL_Delay(10);
	}
	visu_close(window);
}
