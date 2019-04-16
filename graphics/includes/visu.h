/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:26 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/16 22:40:29 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "op.h"
# include "libft.h"
# include "vm.h"
# include <SDL2/SDL.h>
# include <SDL_image.h>
# include "SDL_ttf.h"

# define SCREEN_WIDTH	1600
# define SCREEN_HEIGHT	900
# define COL_GREEN		0x32, 0xCD, 0x32, 0xFF
# define COL_L_GREEN	0x19, 0x66, 0x19, 0xFF
# define COL_BLUE		0x41, 0x69, 0xE1, 0xFF
# define COL_L_BLUE		0x20, 0x34, 0x70, 0xFF
# define COL_RED		0xE3, 0x42, 0x34, 0xFF
# define COL_L_RED		0x71, 0x21, 0x1A, 0xFF
# define COL_YELOW		0xFF, 0xD7, 0x00, 0xFF
# define COL_L_YELOW	0x7F, 0x6B, 0x00, 0xFF
# define COL_WHITE		0xFF, 0xFF, 0xFF, 0xFF
# define COL_BLACK		0x00, 0x00, 0x00, 0xFF
# define COL_GREY		0x30, 0x30, 0x30, 0xFF
# define COL_L_GREY		0x64, 0x64, 0x64, 0xFF
# define STAT_START		0
# define STAT_RUNN		1
# define STAT_PAUSE		2
# define STAT_END		3
# define STAT_QUIT		4
# define STAT_STEP		5

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*back_start;
	SDL_Texture		*back_finish;
	TTF_Font		*f_current;
	TTF_Font		*f_pause;
	TTF_Font		*f_status;
	TTF_Font		*f_arena;
	char			mem_code[MEM_SIZE + 1];
	SDL_Color		color;
	Sint32			width;
	Sint32			height;
	char			status;
	int				speed;
}					t_window;

# define WIN_WIN			(window->window)
# define WIN_REND			(window->window_render)
# define WIN_BACK			(window->background)
# define BACK_START			(window->back_start)
# define BACK_END			(window->back_finish)
# define FONT_CURR			(window->f_current)
# define FONT_PAUSE			(window->f_pause)
# define FONT_STAT			(window->f_status)
# define FONT_ARENA			(window->f_arena)
# define MEM_CODE			(window->mem_code)
# define FONT_COLOR			(window->color)
# define WIN_WID			(window->width)
# define WIN_HEIG			(window->height)
# define WIN_STATUS			(window->status)
# define WIN_SPEED			(window->speed)

/*
** Macro to t_vm
*/

# define VM_CYCLE			(vm->cycles)
# define VM_CYCLE_TO_DIE	(vm->cycles_die)
# define VM_MEMORY			(vm->memory)
# define VM_CHAMP_COUNT		(vm->champion_count)
# define VM_CHAMPS			(vm->champion)
# define VM_P_TOTAL			(vm->p_total)
# define VM_WINNER			(vm->winner)

/*
** visu_int.c
*/
t_window			*init_win(t_vm *vm);
/*
** visu_load.c
*/
int					load_files(t_window *window, t_vm *vm);
/*
** visu_make.c
*/
void				make_background(t_window *window, t_vm *vm);
/*
** visu_events.c
*/
void				win_events(t_window *window);
/*
** visu_print.c
*/
SDL_Color			get_player_color(int player_id);
void				print_str(t_window *window, char *str, int x, int y);
void				print_nbr(t_window *window, int nbr, int x, int y);
void				print_start_names(t_window *window, t_vm *vm);
/*
** visu_render.c
*/
void				render_image(t_window *window, t_vm *vm, t_op op_tab[17]);
//tests
void				render_tests(t_window *window, t_vm *vm);
void				init_tests(t_vm *vm);
#endif
