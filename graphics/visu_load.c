/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:31:09 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/07 18:52:02 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static int		make_background(t_window *window, SDL_Surface *back)
{
	SDL_Texture		*text_back;

	if (!(text_back = SDL_CreateTextureFromSurface(WIN_REND, back)))
		return (0);
	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	SDL_RenderCopy(WIN_REND, text_back, NULL, NULL);
	thickLineRGBA(WIN_REND, 0,
			0, SCREEN_WIDTH,
				SCREEN_HEIGHT, 6, 101, 67, 33, 40);
	SDL_SetRenderTarget(WIN_REND, NULL);
	return (1);
}

int				load_files(t_window *window)
{
	SDL_Surface		*surf_back;

	surf_back = IMG_Load("graphics/imgs/vs2.jpg");
	FONT_NAME = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 40);
	FONT_STAT = TTF_OpenFont("graphics/fonts/Aller_BdIt.ttf", 15);
	if (!surf_back || !FONT_NAME || !FONT_STAT)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));

	WIN_BACK = SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (WIN_BACK == NULL || !make_background(window, surf_back))
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	SDL_FreeSurface(surf_back);
	return (0);
}
