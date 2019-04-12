/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:26 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/12 17:35:07 by mmcclure         ###   ########.fr       */
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
# define COL_WHITE ((SDL_Color){0xFF, 0xFF, 0xFF, 0xFF})
# define STAT_START 0
# define STAT_RUNN 1
# define STAT_PAUSE 2
# define STAT_END 3

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
	int				speed;
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
# define WIN_SPEED	(window->speed)


/*
** Merge
*/

typedef struct			s_champion
{
	char				*filename;
	char				*name;
	char				*comment[2048 + 1];
	unsigned int		size;
	unsigned char		*code; //usseles
	int					id; //usseles
	int					last_live;
	int					lives_in_period;
}						t_champion;

typedef struct			s_proccess
{
	int					position;
	int					carry;
	int					player_id;
	int					id;
	unsigned int		registers[100];
	int					is_live;
	int					command_type;
	int					cycles_to_wait;
	struct s_proccess	*next;
	int					value_written;
	int					pos_written;
}						t_proccess;



typedef struct			vm
{
	int					cycles;
	int					cycles_to_die;
	int					cycles_to_dump;
	int					dump;
	int					cycles_die;
	t_proccess			*process;
	t_champion			**champion;
	int					champion_count;
	t_champion			*winner;
	unsigned char		memory[4096];
	unsigned int		live_exec;
	unsigned int		checkups;
	int					lives[4];
	int					p_num[4];
	int					p_total;
}						t_vm;

# define VM_CYCLE			(vm->cycles)
# define VM_CYCLE_TO_DIE	(vm->cycles_to_die)
# define VM_MEMORY			(vm->memory)
# define VM_CHAMP_COUNT		(vm->champion_count)
# define VM_CHAMPS			(vm->champion)
# define VM_P_TOTAL			(vm->p_total)
# define VM_WINNER			(vm->winner)
# define CYC_DELTA			50 //
# define NBR_LIVE			21 //
# define MAX_CHECKS			21 //


t_window			*init_win(void);
void				win_events(t_window *window);
int					load_files(t_window *window, t_vm *vm);
void				print_str(t_window *window, char *str, int x, int y);
void				render_image(t_window *window, t_vm *vm);

void				print_nbr(t_window *window, int nbr, int x, int y);
void				print_str(t_window *window, char *str, int x, int y);



#endif
