/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/09 18:42:39 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		print_players(t_window *window, int players)
{
	int			i;
	int			height;
	char		*str;
	SDL_Color	colors[4];

	i = 0;
	height = 370;
	colors[0] = (SDL_Color){0, 255, 0, 255};
	colors[1] = (SDL_Color){0, 0, 255, 255};
	colors[2] = (SDL_Color){255, 0, 0, 255};
	colors[3] = (SDL_Color){255, 255, 0, 255};
	while (++i <= players)
	{
		print_str(window, "Player - ", 1235, height += 35);
		str = ft_itoa(i);
		print_str(window, str, 1300, height);
		print_str(window, ":", 1312, height);
		ft_strdel(&str);
		FONT_COLOR = colors[i - 1];
		print_str(window, "TEST_NAME", 1320, height);
		FONT_COLOR = (SDL_Color){255, 255, 255, 255};
		print_str(window, "Last live:", 1250, height += 35);
		print_str(window, "Lives in current period:", 1250, height += 35);
	}
}

static void		make_text(t_window *window, int players)
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
	print_players(window, players);
}

static int		make_background(t_window *window)
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
	make_text(window, 4);
	SDL_SetRenderTarget(WIN_REND, NULL);
	return (1);
}

SDL_Texture		*load_back_pause(t_window *window, SDL_Surface *surf_back)
{
	SDL_Texture		*back_pause;

	back_pause = SDL_CreateTextureFromSurface(WIN_REND, surf_back);
	SDL_SetTextureBlendMode(back_pause, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(back_pause, 150);
	SDL_FreeSurface(surf_back);
	return (back_pause);
}

int				load_files(t_window *window)
{
	SDL_Surface		*surf_back;
	int players = 2;

	if (players == 2)
		surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players == 3)
		surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players == 4)
		surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	else
		surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	FONT_PAUSE = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 50);
	FONT_STAT = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 17);
	if (!surf_back || !FONT_PAUSE || !FONT_STAT)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	BACK_PAUSE = load_back_pause(window, surf_back);
	if (!WIN_BACK || !BACK_PAUSE || !make_background(window))
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	return (0);
}
