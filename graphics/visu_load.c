/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/15 18:09:07 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void				load_text_start_end(t_window *window, int players_count)
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
		return ;
	BACK_START = SDL_CreateTextureFromSurface(WIN_REND, surf);
	SDL_SetTextureBlendMode(BACK_START, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(BACK_START, 150);
	SDL_FreeSurface(surf);
	if (!(surf = IMG_Load("graphics/imgs/end.jpg")))
		return ;
	BACK_END = SDL_CreateTextureFromSurface(WIN_REND, surf);
	SDL_SetTextureBlendMode(BACK_END, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(BACK_END, 150);
	SDL_FreeSurface(surf);
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
	make_background(window, vm);
	load_text_start_end(window, VM_CHAMP_COUNT);
	if (!BACK_START || !BACK_END)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	return (0);
}
