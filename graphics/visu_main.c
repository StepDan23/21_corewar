/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/11 17:27:44 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		visu_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	if (WIN_BACK != NULL)
		SDL_DestroyTexture(WIN_BACK);
	if (FONT_PAUSE != NULL)
		TTF_CloseFont(FONT_PAUSE);
	SDL_DestroyWindow(WIN_WIN);
	FONT_STAT = NULL;
	FONT_PAUSE = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(1);
}

static t_run	*init_running(void)
{
	t_run		*running;

	running = (t_run*)malloc(sizeof(t_run));
	PLA_COUNT = 4;
	RUN_SPEED = 50;
	RUN_CYCLE = 0;
	RUN_TMP = 0;
	RUN_PROC = 2;
	CYC_DIE = 100;
	CYC_DELTA = 50;
	NBR_LIVE = 21;
	MAX_CHECKS = 10;
	return (running);
}

static t_player		**init_players(int num_players)
{
	t_player		**players;

	players = (t_player**)malloc(sizeof(t_player) * (num_players + 1));
	players[num_players] = NULL;
	while (--num_players >= 0)
	{
		players[num_players] = (t_player*)malloc(sizeof(t_player));
		players[num_players]->name = ft_strnew(10);
		ft_strcpy(players[num_players]->name, "Test_player ;)");
		players[num_players]->last_live = 0;
		players[num_players]->lives_in_period = 0;
	}
	return (players);
}

static void			get_player_color(t_window	*window, t_run *running, int i)
{
	if (i >= 0 && i < 23)
		FONT_COLOR = COL_GREEN;
	else if (i >= 4096 / PLA_COUNT && i < 4096 / PLA_COUNT + 23 && PLA_COUNT > 1)
		FONT_COLOR = COL_BLUE;
	else if (i >= 2 * 4096 / PLA_COUNT && i < 2 * 4096 / PLA_COUNT + 23 && PLA_COUNT > 2)
		FONT_COLOR = COL_RED;
	else if (i >= 3 * 4096 / PLA_COUNT && i < 3 * 4096 / PLA_COUNT + 23 && PLA_COUNT > 3)
		FONT_COLOR = COL_YELOW;
	else
		FONT_COLOR = (SDL_Color){0x64, 0x64, 0x64, 0xFF};
}

static void			init_back_arena(t_window	*window, t_run *running, unsigned char *first_state)
{
	int			i;
	int			j;
	char		*hex;
	char		str[3];

	hex = "0123456789abcdef";
	FONT_CURR = FONT_ARENA;
	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	j = 0;
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			get_player_color(window, running, j * 64 + i);
			str[0] = hex[(first_state[j * 64 + i] / 16)];
			str[1] = hex[(first_state[j * 64 + i] % 16)];
			str[2] = '\0';
			print_str(window, str, 13 + 18.7 * i , 15 + 13.5 * j);
			i++;
		}
		j++;
	}
	SDL_SetRenderTarget(WIN_REND, NULL);
	FONT_COLOR = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
}

int				main(void)
{
	t_window	*window;
	t_run		*running;
	t_player	**players;
	unsigned char *first_state;

	first_state = (unsigned char*)ft_strnew(4 * 1024);
	ft_strcpy((char*)first_state, "LOL KEK");
	if (!(window = init_win()))
		return (0);
	if (!(running = init_running()))
		WIN_QUIT = 1;
	if (!(players = init_players(PLA_COUNT)))
		WIN_QUIT = 1;
	if (load_files(window, players, running) != 0)
		WIN_QUIT = 1;
	init_back_arena(window, running, first_state);
	while (!WIN_QUIT)
	{
		// SDL_RenderClear(WIN_REND);
		win_events(window, running);
		render_image(window, running, players);
		SDL_RenderPresent(WIN_REND);
		// SDL_Delay(1);
	}
	visu_close(window);
}
