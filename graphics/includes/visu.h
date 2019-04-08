/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:26 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/08 18:43:31 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 900

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
	TTF_Font		*f_names;
	TTF_Font		*f_status;
	SDL_Color		color;
	char			quit;
	char			status;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define BACK_PAUSE	(window->back_pause)
# define FONT_NAME	(window->f_names)
# define FONT_STAT	(window->f_status)
# define FONT_COLOR	(window->color)
# define WIN_QUIT	(window->quit)
# define WIN_STATUS	(window->status)



typedef struct		s_print
{
	SDL_Color	color;
	char		*str;
}					t_print;

t_window		*visu_init_win(void);
void			win_events(t_window *window);
int				load_files(t_window *window);
void			print_str(t_window *window, char *str, int x, int y);
#endif
