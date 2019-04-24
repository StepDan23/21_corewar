/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/24 15:22:06 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void			visu_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	if (WIN_BACK != NULL)
		SDL_DestroyTexture(WIN_BACK);
	if (FONT_PAUSE != NULL)
		TTF_CloseFont(FONT_PAUSE);
	SDL_DestroyWindow(WIN_WIN);
	Mix_FreeChunk(AUDIO_PLAY);
	Mix_FreeChunk(AUDIO_START);
	Mix_FreeChunk(AUDIO_SPEED);
	Mix_FreeChunk(AUDIO_SLOW);
	// gScratch = NULL;
	// gHigh = NULL;
	// gMedium = NULL;
	// gLow = NULL;
	// Mix_FreeMusic( gMusic );
	// gMusic = NULL;
	FONT_STAT = NULL;
	FONT_PAUSE = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	exit(1);
}

int					main(int argc, char **argv)
{
	t_window		*window;
	t_vm			*vm;
	t_op			op_tab[17];

	if (!(vm = init_vm_test(argc, argv)))
		exit(0);
	if (!(window = init_win(vm)))
		exit(0);
	if (load_files(window, vm) != 0)
		exit(0);
	make_background(window, vm);
	init_optab(op_tab);
//music start
Mix_PlayChannel( -1, AUDIO_START, 0 );
Mix_PlayChannel( -1, AUDIO_PLAY, -1);
init_tests(vm);
	while (WIN_STATUS != STAT_QUIT)
	{
		if (vm->end_game)
		{
			WIN_STATUS = STAT_END;
//music finish
		}
		render_image(window, vm, op_tab);
		SDL_RenderPresent(WIN_REND);
		win_events(window);
	}
	visu_close(window);
}
