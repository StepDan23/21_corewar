/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:13:50 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/25 13:10:05 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		init_win_consts(t_window *window, t_vm *vm, int i)
{
	i = -1;
	while (++i <= MEM_SIZE)
	{
		if (i >= 0 && i < (int)VM_CHAMPS[0]->size)
			MEM_CODE[i] = 1;
		else if (i >= (4096 / VM_CHAMP_COUNT) && VM_CHAMP_COUNT > 1 &&
					i < (int)(4096 / VM_CHAMP_COUNT + VM_CHAMPS[1]->size))
			MEM_CODE[i] = 2;
		else if (i >= (2 * 4096 / VM_CHAMP_COUNT) && VM_CHAMP_COUNT > 2 &&
				i < (int)(2 * 4096 / VM_CHAMP_COUNT + VM_CHAMPS[2]->size))
			MEM_CODE[i] = 3;
		else if (i >= (3 * 4096 / VM_CHAMP_COUNT) && VM_CHAMP_COUNT > 3 &&
				i < (int)(3 * 4096 / VM_CHAMP_COUNT + VM_CHAMPS[3]->size))
			MEM_CODE[i] = 4;
		else
			MEM_CODE[i] = 0;
		MEM_CARR[i] = 0;
	}
	FONT_COLOR = (SDL_Color){COL_WHITE};
	WIN_WID = SCREEN_WIDTH;
	WIN_HEIG = SCREEN_HEIGHT;
	WIN_STATUS = STAT_START;
	WIN_SPEED = 50;
	WIN_VOLUME = 0;
}

t_window		*init_win(t_vm *vm)
{
	t_window	*window;

	if (!(window = (t_window*)malloc(sizeof(t_window))))
		return (NULL);
	init_win_consts(window, vm, 0);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || TTF_Init() < 0)
	{
		ft_printf("Init_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_WIN = SDL_CreateWindow("Vizualizer", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (WIN_WIN == NULL)
	{
		ft_printf("Init_Window_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_REND = SDL_CreateRenderer(WIN_WIN, -1, SDL_RENDERER_ACCELERATED);
	if (WIN_REND == NULL)
	{
		ft_printf("Init_Renderer_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	return (window);
}
