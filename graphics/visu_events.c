/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:36:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/09 18:48:20 by mmcclure         ###   ########.fr       */
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

static void		event_speed(t_window *window, t_run *running, SDL_Keycode key)
{
	if (key == SDLK_UP && RUN_SPEED < 1000)
	{
		RUN_SPEED += 1;
		if (RUN_SPEED > 1000)
			RUN_SPEED = 1000;
	}
	else if (key == SDLK_RIGHT && RUN_SPEED < 1000)
	{
		RUN_SPEED += 10;
		if (RUN_SPEED > 1000)
			RUN_SPEED = 1000;
	}
	else if (key == SDLK_DOWN && RUN_SPEED > 1)
	{
		RUN_SPEED -= 1;
		if (RUN_SPEED < 1)
			RUN_SPEED = 1;
	}
	else if (key == SDLK_LEFT && RUN_SPEED > 1)
	{
		RUN_SPEED -= 10;
		if (RUN_SPEED < 1)
			RUN_SPEED = 1;
	}
}

void			win_events(t_window *window, t_run *running)
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
			if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN ||
				e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
				event_speed(window, running, e.key.keysym.sym);
			if (WIN_STATUS == 3)
				WIN_QUIT = 1;
		}
		if (e.type == SDL_WINDOWEVENT &&
							e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			WIN_WID = e.window.data1;
			WIN_HEIG = e.window.data2;
		}
	}
}
