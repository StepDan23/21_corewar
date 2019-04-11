/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:26 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/11 17:27:01 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 900
# define COL_GREEN ((SDL_Color){84, 190, 56, 0xFF})
# define COL_BLUE ((SDL_Color){4, 46, 191, 0xFF})
# define COL_RED ((SDL_Color){186, 48, 27, 0xFF})
# define COL_YELOW ((SDL_Color){0xFF, 0xFF, 0, 0xFF})

# include "../../libft/includes/libft.h"
# include <SDL2_gfxPrimitives.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*back_pause;
	SDL_Texture		*back_finish;
	TTF_Font		*f_current;
	TTF_Font		*f_pause;
	TTF_Font		*f_status;
	TTF_Font		*f_arena;
	SDL_Color		color;
	Sint32			width;
	Sint32			height;
	char			quit;
	char			status;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define BACK_PAUSE	(window->back_pause)
# define BACK_FIN	(window->back_finish)
# define FONT_CURR	(window->f_current)
# define FONT_PAUSE	(window->f_pause)
# define FONT_STAT	(window->f_status)
# define FONT_ARENA	(window->f_arena)
# define FONT_COLOR	(window->color)
# define WIN_WID	(window->width)
# define WIN_HEIG	(window->height)
# define WIN_QUIT	(window->quit)
# define WIN_STATUS	(window->status)

typedef struct		s_run
{
	int				players_count;
	float			cycle;
	int				tmp;
	int				speed;
	int				processes;
	int				cyc_die;
	int				cyc_delta;
	int				nbr_live;
	int				max_checks;
}					t_run;

# define PLA_COUNT	(running->players_count)
# define RUN_CYCLE	(running->cycle)
# define RUN_TMP	(running->tmp)
# define RUN_SPEED	(running->speed)
# define RUN_PROC	(running->processes)
# define CYC_DIE	(running->cyc_die)
# define CYC_DELTA	(running->cyc_delta)
# define NBR_LIVE	(running->nbr_live)
# define MAX_CHECKS	(running->max_checks)

typedef struct		s_player
{
	char			*name;
	int				last_live;
	int				lives_in_period;
}					t_player;

t_window			*init_win(void);
void				win_events(t_window *window, t_run *running);
int					load_files(t_window *window, t_player **players, t_run *running);
void				print_str(t_window *window, char *str, int x, int y);
void				render_image(t_window *window, t_run *running, t_player **players);

void				print_nbr(t_window *window, int nbr, int x, int y);
void				print_str(t_window *window, char *str, int x, int y);
#endif
