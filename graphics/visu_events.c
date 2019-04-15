/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:36:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/15 14:34:19 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		event_space(t_window *window)
{
	if (WIN_STATUS == STAT_START)
		WIN_STATUS = STAT_RUNN;
	else if (WIN_STATUS == STAT_RUNN)
		WIN_STATUS = STAT_PAUSE;
	else if (WIN_STATUS == STAT_PAUSE)
		WIN_STATUS = STAT_RUNN;
}

static void		event_speed(t_window *window, SDL_Keycode key)
{
	if (key == SDLK_UP && WIN_SPEED < 1000)
	{
		WIN_SPEED += 1;
		if (WIN_SPEED > 1000)
			WIN_SPEED = 1000;
	}
	else if (key == SDLK_RIGHT && WIN_SPEED < 1000)
	{
		WIN_SPEED += 10;
		if (WIN_SPEED > 1000)
			WIN_SPEED = 1000;
	}
	else if (key == SDLK_DOWN && WIN_SPEED > 1)
	{
		WIN_SPEED -= 1;
		if (WIN_SPEED < 1)
			WIN_SPEED = 1;
	}
	else if (key == SDLK_LEFT && WIN_SPEED > 1)
	{
		WIN_SPEED -= 10;
		if (WIN_SPEED < 1)
			WIN_SPEED = 1;
	}
}

void			win_events(t_window *window)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			WIN_STATUS = STAT_QUIT;
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				WIN_STATUS = STAT_QUIT;
			if (e.key.keysym.sym == SDLK_SPACE)
				event_space(window);
			if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN ||
				e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
				event_speed(window, e.key.keysym.sym);
			if (WIN_STATUS == STAT_END)
				WIN_STATUS = STAT_QUIT;
		}
		if (e.type == SDL_WINDOWEVENT &&
							e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			WIN_WID = e.window.data1;
			WIN_HEIG = e.window.data2;
		}
	}
}
