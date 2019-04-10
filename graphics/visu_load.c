/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/10 19:00:20 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		print_players(t_window *window, t_player **players)
{
	int			i;
	int			height;
	SDL_Color	colors[4];

	i = 0;
	height = 370;
	colors[0] = (SDL_Color){0, 255, 0, 255};
	colors[1] = (SDL_Color){0, 0, 255, 255};
	colors[2] = (SDL_Color){255, 0, 0, 255};
	colors[3] = (SDL_Color){255, 255, 0, 255};
	while (players[i] != NULL)
	{
		print_str(window, "Player - ", 1235, height += 35);
		print_nbr(window, i, 1300, height);
		print_str(window, ":", 1312, height);
		FONT_COLOR = colors[i];
		print_str(window, players[i]->name, 1324, height);
		FONT_COLOR = (SDL_Color){255, 255, 255, 255};
		print_str(window, "Last live:", 1250, height += 35);
		print_str(window, "Lives in current period:", 1250, height += 35);
		i++;
	}
}

static void		make_text(t_window *window, t_player **players)
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

static int		make_background(t_window *window, t_player **players)
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
	make_text(window, players);
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

static	void	make_textures(t_window *window, t_player **players, int players_count)
{
	
}

static SDL_Surface		*load_pause_back(int players_count)
{
	SDL_Surface		*surf_pause;

	if (players_count == 2)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players_count == 3)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (players_count == 4)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	return (surf_pause);
}

int						load_files(t_window *window, t_player **players, t_run *running)
{
	SDL_Surface		*surf_pause;

	if (PLA_COUNT == 2)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (PLA_COUNT == 3)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else if (PLA_COUNT == 4)
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	else
		surf_pause = IMG_Load("graphics/imgs/vs2.jpg");
	FONT_PAUSE = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 50);
	FONT_STAT = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 17);
	if (!surf_pause || !FONT_PAUSE || !FONT_STAT)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	BACK_RUN = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	BACK_PAUSE = load_back_pause(window, surf_pause);
	if (!WIN_BACK || !BACK_PAUSE || !BACK_RUN || !make_background(window, players))
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	return (0);
}
