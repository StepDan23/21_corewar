/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/25 14:01:18 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void			visu_close(t_window *window)
{
	SDL_DestroyRenderer(WIN_REND);
	WIN_REND = NULL;
	SDL_DestroyTexture(WIN_BACK);
	WIN_BACK = NULL;
	TTF_CloseFont(FONT_PAUSE);
	FONT_PAUSE = NULL;
	SDL_DestroyWindow(WIN_WIN);
	WIN_WIN = NULL;
	Mix_FreeChunk(AUDIO_MAIN);
	AUDIO_MAIN = NULL;
	Mix_FreeChunk(AUDIO_START);
	AUDIO_START = NULL;
	Mix_FreeChunk(AUDIO_END);
	AUDIO_END = NULL;
	Mix_FreeChunk(AUDIO_SPEED);
	AUDIO_SPEED = NULL;
	Mix_FreeChunk(AUDIO_SLOW);
	AUDIO_SLOW = NULL;
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

	if ((!(vm = init_vm_test(argc, argv))) ||
					(!(window = init_win(vm))) ||
						(load_files(window, vm) != 0))
		exit(0);
	make_background(window, vm);
	init_optab(op_tab);
	Mix_Volume(-1, WIN_VOLUME);
	Mix_PlayChannel(1, AUDIO_START, 0);
	while (WIN_STATUS != STAT_QUIT)
	{
		if (vm->end_game)
		{
			WIN_STATUS = STAT_END;
			Mix_PlayChannel(2, AUDIO_END, -1);
			vm->end_game = 0;
		}
		render_image(window, vm, op_tab);
		SDL_RenderPresent(WIN_REND);
		win_events(window);
	}
	visu_close(window);
}
