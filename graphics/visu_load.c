/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/08 15:46:49 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		print_str(t_window *window,
						char *str, int x, int y)
{
	SDL_Surface		*text_surf;
	SDL_Texture		*text;
	SDL_Rect		dst;

	text_surf = TTF_RenderText_Blended(FONT_STAT, str, FONT_COLOR);
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	dst = (SDL_Rect){x, y, text_surf->w, text_surf->h};
	SDL_RenderCopy(WIN_REND, text, NULL, &dst);
	SDL_FreeSurface(text_surf);
	SDL_DestroyTexture(text);
}

static void		print_players(t_window *window, int players)
{
	int			i;
	int			height;
	char		*str;
	SDL_Color	colors[4];

	i = 0;
	height = 300;
	colors[0] = (SDL_Color){0, 255, 0, 255};
	colors[1] = (SDL_Color){0, 0, 255, 255};
	colors[2] = (SDL_Color){255, 0, 0, 255};
	colors[3] = (SDL_Color){255, 255, 0, 255};
	while (++i <= players)
	{
		print_str(window, "Player - ", 1235, height += 30);
		str = ft_itoa(i);
		print_str(window, str, 1300, height);
		print_str(window, ":", 1312, height);
		ft_strdel(&str);
		FONT_COLOR = colors[i - 1];
		print_str(window, "TEST_NAME", 1320, height);
		FONT_COLOR = (SDL_Color){255, 255, 255, 255};
		print_str(window, "Last live:", 1250, height += 30);
		print_str(window, "Lives in current period:", 1250, height += 30);
	}
}

static void		make_text(t_window *window, int players)
{
	SDL_Rect	*dst;
	int			height;

	height = 50;
	print_str(window, "Cycles/second limit   [<-|->]:", 1235, height += 30);
	print_str(window, "Cycle:", 1235, height += 30);
	print_str(window, "Processes:", 1235, height += 30);
	print_str(window, "CYCLE_TO_DIE:", 1235, height += 30);
	print_str(window, "CYCLE_DELTA:", 1235, height += 30);
	print_str(window, "NBR_LIVE:", 1235, height += 30);
	print_str(window, "MAX_CHECKS:", 1235, height += 30);
	print_players(window, players);
	// print_str(window, "MAX_CHECKS:", 1235, 260);
	// print_str(window, "MAX_CHECKS:", 1235, 260);
	// print_str(window, "MAX_CHECKS:", 1235, 260);
	// print_str(window, "MAX_CHECKS:", 1235, 260);
}

static int		make_background(t_window *window, SDL_Surface *back)
{
	SDL_Texture		*text_back;
	SDL_Rect		rects[3];

	if (!(text_back = SDL_CreateTextureFromSurface(WIN_REND, back)))
		return (0);
	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	SDL_SetRenderDrawColor(WIN_REND, 0x64, 0x64, 0x64, 0xFF);
	SDL_RenderClear(WIN_REND);
	SDL_SetRenderDrawColor(WIN_REND, 0x30, 0x30, 0x30, 0xFF);
	rects[0] = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	rects[1] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, 15,
								SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.32};
	rects[2] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, SCREEN_HEIGHT * 0.32 + 30,
							SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.68 - 45};
	SDL_RenderFillRects(WIN_REND, rects, 3);
	make_text(window, 4);
	SDL_DestroyTexture(text_back);
	SDL_SetRenderTarget(WIN_REND, NULL);
	return (1);
}

int				load_files(t_window *window)
{
	SDL_Surface		*surf_back;

	surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	FONT_NAME = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 40);
	FONT_STAT = TTF_OpenFont("graphics/fonts/OpenSans-Regular.ttf", 17);
	if (!surf_back || !FONT_NAME || !FONT_STAT)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (WIN_BACK == NULL || !make_background(window, surf_back))
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	SDL_FreeSurface(surf_back);
	return (0);
}
