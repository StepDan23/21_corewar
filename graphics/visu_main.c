/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/09 19:09:54 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		visu_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	if (WIN_BACK != NULL)
		SDL_DestroyTexture(WIN_BACK);
	if (FONT_PAUSE != NULL)
		TTF_CloseFont(FONT_PAUSE);
	SDL_DestroyWindow(WIN_WIN);
	FONT_STAT = NULL;
	FONT_PAUSE = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(1);
}

static t_run	*init_running(void)
{
	t_run		*running;

	running = (t_run*)malloc(sizeof(t_run));
	RUN_SPEED = 50;
	RUN_CYCLE = 0;
	RUN_TMP = 0;
	RUN_PROC = 2;
	CYC_DIE = 100;
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
		win_events(window, running);
		SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
		render_image(window, running);
		SDL_RenderPresent(WIN_REND);
		SDL_Delay(20);
	}
	visu_close(window);
}
