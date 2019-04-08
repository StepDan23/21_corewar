/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/08 18:47:25 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		visu_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	// if (WIN_BACK != NULL)
	// 	SDL_DestroyTexture(WIN_BACK);
	if (FONT_NAME != NULL)
		TTF_CloseFont(FONT_NAME);
	SDL_DestroyWindow(WIN_WIN);
	FONT_STAT = NULL;
	FONT_NAME = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	// IMG_Quit();
	SDL_Quit();
	// exit(1);
}

static void		render_pause(t_window *window)
{
	SDL_RenderCopy(WIN_REND, BACK_PAUSE, NULL, NULL);
	if (WIN_STATUS == 0)
		print_str(window, "Press SPACE to start", 100, 100);
	if (WIN_STATUS == 2)
		print_str(window, "Press SPACE to continue", 100, 100);
}

int				main(void)
{
	t_window	*window;

	if (!(window = visu_init_win()))
		return (0);
	if (load_files(window) != 0)
		WIN_QUIT = 1;
	while (!WIN_QUIT)
	{
		win_events(window);
		SDL_RenderClear(WIN_REND);
		SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
		if (WIN_STATUS == 0 || WIN_STATUS == 2)
			render_pause(window);
		SDL_RenderPresent(WIN_REND);
		SDL_Delay(10);
	}
	visu_close(window);
}
