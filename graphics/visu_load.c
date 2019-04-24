/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/24 17:41:31 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int				load_text_start_end(t_window *window, int players_count)
{
	SDL_Surface		*surf;

	BACK_START = NULL;
	BACK_END = NULL;
	if (players_count == 2)
		surf = IMG_Load("graphics/imgs/2_pla.jpg");
	else if (players_count == 3)
		surf = IMG_Load("graphics/imgs/3_pla.jpg");
	else if (players_count == 4)
		surf = IMG_Load("graphics/imgs/4_pla.jpg");
	else
		surf = IMG_Load("graphics/imgs/1_pla.jpg");
	if (!surf)
		return (0);
	BACK_START = SDL_CreateTextureFromSurface(WIN_REND, surf);
	SDL_SetTextureBlendMode(BACK_START, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(BACK_START, 150);
	SDL_FreeSurface(surf);
	if (!(surf = IMG_Load("graphics/imgs/end.jpg")))
		return (0);
	BACK_END = SDL_CreateTextureFromSurface(WIN_REND, surf);
	SDL_SetTextureBlendMode(BACK_END, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(BACK_END, 150);
	SDL_FreeSurface(surf);
	return (1);
}

static int				load_sounds(t_window *window)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (0);
	AUDIO_MAIN = Mix_LoadWAV("graphics/music/play1.wav");
	AUDIO_START = Mix_LoadWAV("graphics/music/start.wav");
	AUDIO_SPEED = Mix_LoadWAV("graphics/music/speedup.wav");
	AUDIO_SLOW = Mix_LoadWAV("graphics/music/slowdown.wav");
	AUDIO_END = Mix_LoadWAV("graphics/music/end_of_game.wav");
	if (!AUDIO_MAIN || !AUDIO_SLOW || !AUDIO_SPEED ||
									!AUDIO_START || !AUDIO_END)
	{
		ft_printf("Failed to load sound effects!\n");
		return (0);
	}
	return (1);
}

int						load_files(t_window *window, t_vm *vm)
{
	FONT_PAUSE = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 50);
	FONT_STAT = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 17);
	FONT_ARENA = TTF_OpenFont("graphics/fonts/DroidSansMono.ttf", 12);
	FONT_CURR = FONT_STAT;
	if (!FONT_PAUSE || !FONT_STAT || !FONT_ARENA)
		return (ft_printf("Load_Error: %s\n", TTF_GetError()));
	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!WIN_BACK)
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	if (!load_text_start_end(window, VM_CHAMP_COUNT))
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	if (!load_sounds(window))
		return (ft_printf("Audio_Init_Error: %s\n", Mix_GetError()));
	return (0);
}
