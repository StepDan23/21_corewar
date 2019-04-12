/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:41:52 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/11 19:27:00 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

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
