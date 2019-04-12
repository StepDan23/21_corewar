/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/12 17:24:18 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		print_players(t_window *window, t_vm *vm)
{
	int			i;
	int			height;
	SDL_Color	colors[4];

	i = 0;
	height = 350;
	colors[0] = COL_GREEN;
	colors[1] = COL_BLUE;
	colors[2] = COL_RED;
	colors[3] = COL_YELOW;
	while (VM_CHAMPS[i] != NULL)
	{
		print_str(window, "Player - ", 1235, height += 60);
		print_nbr(window, i, 1300, height);
		print_str(window, ":", 1312, height);
		FONT_COLOR = colors[i];
		print_str(window, VM_CHAMPS[i]->name, 1324, height);
		FONT_COLOR = (SDL_Color){255, 255, 255, 255};
		print_str(window, "Last live:", 1250, height += 30);
		print_str(window, "Lives in current period:", 1250, height += 30);
		i++;
	}
}

static void		print_text(t_window *window)
{
	int			height;

	height = 80;
	print_str(window, "Cycles/second limit   [<-|->]:", 1235, height += 35);
	print_str(window, "Cycle:", 1235, height += 35);
	print_str(window, "Processes:", 1235, height += 35);
	print_str(window, "CYCLE_TO_DIE:", 1235, height += 35);
	print_str(window, "CYCLE_DELTA:", 1235, height += 35);
	print_str(window, "NBR_LIVE:", 1235, height += 35);
	print_str(window, "MAX_CHECKS:", 1235, height += 35);
}

static void		make_background(t_window *window, t_vm *vm)
{
	SDL_Rect		rects[3];

	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	SDL_SetRenderDrawColor(WIN_REND, 0x64, 0x64, 0x64, 0xFF);
	SDL_RenderClear(WIN_REND);
	SDL_SetRenderDrawColor(WIN_REND, 0x30, 0x30, 0x30, 0xFF);
	rects[0] = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	rects[1] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, 15,
								SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.4};
	rects[2] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, SCREEN_HEIGHT * 0.4 + 30,
							SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.6 - 45};
	SDL_RenderFillRects(WIN_REND, rects, 3);
	print_text(window);
	print_players(window, vm);
	SDL_SetRenderTarget(WIN_REND, NULL);
}

static SDL_Texture		*load_texture_pause(t_window *window, int players_count)
{
	SDL_Surface		*surf_pause;
	SDL_Texture		*text_pause;

	if (players_count == 2)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players_count == 3)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players_count == 4)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	if (!surf_pause)
		return (NULL);
	text_pause = SDL_CreateTextureFromSurface(WIN_REND, surf_pause);
	SDL_SetTextureBlendMode(text_pause, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(text_pause, 150);
	SDL_FreeSurface(surf_pause);
	return (text_pause);
}

int						load_files(t_window *window, t_vm *vm)
{
	FONT_PAUSE = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 50);
	FONT_STAT = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 17);
	FONT_ARENA = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 13);
	FONT_CURR = FONT_STAT;
	if (!FONT_PAUSE || !FONT_STAT || !FONT_ARENA)
		return (ft_printf("Load_Error: %s\n",  TTF_GetError()));
	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!WIN_BACK)
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	make_background(window, vm);
	if (!(BACK_PAUSE = load_texture_pause(window, VM_CHAMP_COUNT)))
		return (ft_printf("Load_Error: %s\n",  SDL_GetError()));
	return (0);
}
