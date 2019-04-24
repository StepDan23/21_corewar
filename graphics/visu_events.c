/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:36:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/24 17:40:23 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		event_space(t_window *window)
{
	if (WIN_STATUS == STAT_START)
	{
		WIN_STATUS = STAT_RUNN;
		Mix_PlayChannel(1, AUDIO_SPEED, 0);
		Mix_PlayChannel(2, AUDIO_MAIN, -1);
	}
	else if (WIN_STATUS == STAT_RUNN)
	{
		WIN_STATUS = STAT_PAUSE;
		Mix_PlayChannel(1, AUDIO_SLOW, 0);
		Mix_Pause(2);
	}
	else if (WIN_STATUS == STAT_PAUSE)
	{
		WIN_STATUS = STAT_RUNN;
		Mix_PlayChannel(1, AUDIO_SPEED, 0);
		Mix_Resume(2);
	}
}

static void		event_speed(t_window *window, SDL_Keycode key)
{
	if ((key == SDLK_RIGHT || key == SDLK_r) && WIN_SPEED < 1000)
	{
		WIN_SPEED += 50;
		if (WIN_SPEED > 1000)
			WIN_SPEED = 1000;
	}
	else if ((key == SDLK_LEFT || key == SDLK_q) && WIN_SPEED > 50)
	{
		WIN_SPEED -= 50;
		if (WIN_SPEED < 50)
			WIN_SPEED = 50;
	}
}

void			key_pressed(t_window *window, SDL_Keycode key)
{
	if (WIN_STATUS == STAT_END)
		WIN_STATUS = STAT_QUIT;
	else if (key == SDLK_ESCAPE)
		WIN_STATUS = STAT_QUIT;
	else if (key == SDLK_SPACE)
		event_space(window);
	else if (key == SDLK_q || key == SDLK_r ||
					key == SDLK_LEFT || key == SDLK_RIGHT)
		event_speed(window, key);
	else if (key == SDLK_s)
		WIN_STATUS = STAT_STEP;
	else if (key == SDLK_m)
	{
		if (WIN_VOLUME == 128)
			WIN_VOLUME = 0;
		else
			WIN_VOLUME = 128;
		Mix_Volume(-1, WIN_VOLUME);
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
			key_pressed(window, e.key.keysym.sym);
		if (e.type == SDL_WINDOWEVENT &&
					e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			WIN_WID = e.window.data1;
			WIN_HEIG = e.window.data2;
		}
	}
}
