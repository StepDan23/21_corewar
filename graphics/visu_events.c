/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:36:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/09 12:56:46 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		event_space(t_window *window)
{
	if (WIN_STATUS == 0)
		WIN_STATUS = 1;
	else if (WIN_STATUS == 1)
		WIN_STATUS = 2;
	else if (WIN_STATUS == 2)
		WIN_STATUS = 1;
}

void			win_events(t_window *window)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			WIN_QUIT = 1;
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				WIN_QUIT = 1;
			if (e.key.keysym.sym == SDLK_SPACE)
				event_space(window);
			if (WIN_STATUS == 3)
				WIN_QUIT = 1;
		}
		if (e.type == SDL_WINDOWEVENT 
			&& e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				WIN_WID = e.window.data1;
				WIN_HEIG = e.window.data2;
			}
	}
}
