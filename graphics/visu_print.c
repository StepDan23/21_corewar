/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:41:52 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/24 11:41:29 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

SDL_Color	get_player_color(int player_id)
{
	SDL_Color	colors[10];

	colors[0] = (SDL_Color){COL_L_GREY};
	colors[1] = (SDL_Color){COL_GREEN};
	colors[2] = (SDL_Color){COL_BLUE};
	colors[3] = (SDL_Color){COL_RED};
	colors[4] = (SDL_Color){COL_YELOW};
	colors[5] = (SDL_Color){COL_GREY};
	colors[6] = (SDL_Color){COL_L_GREEN};
	colors[7] = (SDL_Color){COL_L_BLUE};
	colors[8] = (SDL_Color){COL_L_RED};
	colors[9] = (SDL_Color){COL_L_YELOW};
	if (player_id > 9)
		return (colors[player_id % 5 + 5]);
	return (colors[player_id]);
}

void		print_str(t_window *window, char *str, int x, int y)
{
	SDL_Surface		*text_surf;
	SDL_Texture		*text;
	SDL_Rect		dst;

	text_surf = TTF_RenderText_Blended(FONT_CURR, str, FONT_COLOR);
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	dst = (SDL_Rect){x, y, text_surf->w, text_surf->h};
	SDL_RenderCopy(WIN_REND, text, NULL, &dst);
	SDL_FreeSurface(text_surf);
	SDL_DestroyTexture(text);
}

void		print_nbr(t_window *window, int nbr, int x, int y)
{
	char	*nbr_text;

	nbr_text = ft_itoa(nbr);
	print_str(window, nbr_text, x, y);
	ft_strdel(&nbr_text);
}

void		print_start_names(t_window *window, t_vm *vm)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	FONT_COLOR = (SDL_Color){COL_L_BLUE};
	if (VM_CHAMP_COUNT == 1)
	{
		print_str(window, "What? Only one player???", 313, 110);
		print_str(window, "Okay then...", 472, 200);
	}
	FONT_COLOR = (SDL_Color){COL_BLACK};
	while (VM_CHAMPS[i])
	{
		x = 9 + 1200 * (i + 1) / (VM_CHAMP_COUNT) - (600 / VM_CHAMP_COUNT) -
											ft_strlen(VM_CHAMPS[i]->name) * 13;
		y = (i % 2 == 0) ? 290 : 540;
		print_str(window, VM_CHAMPS[i]->name, x, y);
		i++;
	}
}
