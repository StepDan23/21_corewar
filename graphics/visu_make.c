/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 10:34:07 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/25 13:56:13 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		make_back_arena(t_window *window, t_vm *vm)
{
	int			i;
	int			j;
	char		*hex;
	char		str[3];

	hex = "0123456789abcdef";
	FONT_CURR = FONT_ARENA;
	j = 0;
	str[2] = '\0';
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			str[0] = hex[VM_MEMORY[j * 64 + i] / 16];
			str[1] = hex[VM_MEMORY[j * 64 + i] % 16];
			FONT_COLOR = get_player_color(MEM_CODE[j * 64 + i]);
			print_str(window, str, 14 + 18.7 * i, 20 + 13.5 * j);
			i++;
		}
		j++;
	}
}

static void		make_text_players(t_window *window, t_vm *vm)
{
	int			i;
	int			height;

	i = 0;
	height = 350;
	while (VM_CHAMPS[i] != NULL)
	{
		print_str(window, "Player - ", 1235, height += 60);
		print_nbr(window, i, 1300, height);
		print_str(window, ":", 1312, height);
		FONT_COLOR = get_player_color(i + 1);
		print_str(window, VM_CHAMPS[i]->name, 1324, height);
		FONT_COLOR = (SDL_Color){COL_WHITE};
		print_str(window, "Last live:", 1250, height += 30);
		print_str(window, "Lives in current period:", 1250, height += 30);
		i++;
	}
}

static void		make_text_status(t_window *window)
{
	int			height;

	height = 70;
	FONT_COLOR = (SDL_Color){COL_WHITE};
	print_str(window, "Cycles/second limit   [<-|->]:", 1235, height += 35);
	print_str(window, "Cycle:", 1235, height += 35);
	print_str(window, "Processes:", 1235, height += 35);
	print_str(window, "CYCLE_TO_DIE:", 1235, height += 35);
	print_str(window, "CYCLE_DELTA:", 1235, height += 35);
	print_str(window, "NBR_LIVE:", 1235, height += 35);
	print_str(window, "MAX_CHECKS:", 1235, height += 35);
	print_str(window, "sound on/off [ M ]", 1335, height += 35);
}

void			make_background(t_window *window, t_vm *vm)
{
	SDL_Rect		rects[3];

	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	SDL_SetRenderDrawColor(WIN_REND, COL_L_GREY);
	SDL_RenderClear(WIN_REND);
	SDL_SetRenderDrawColor(WIN_REND, COL_GREY);
	rects[0] = (SDL_Rect){9, 15, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT - 30};
	rects[1] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, 15,
								SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.4};
	rects[2] = (SDL_Rect){SCREEN_WIDTH * 0.75 + 18, SCREEN_HEIGHT * 0.4 + 30,
							SCREEN_WIDTH * 0.25 - 27, SCREEN_HEIGHT * 0.6 - 45};
	SDL_RenderFillRects(WIN_REND, rects, 3);
	make_text_status(window);
	make_text_players(window, vm);
	make_back_arena(window, vm);
	SDL_SetRenderTarget(WIN_REND, NULL);
}
