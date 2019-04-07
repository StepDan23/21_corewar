/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:26 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/07 18:40:05 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define SCREEN_WIDTH 1200
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
	TTF_Font		*f_names;
	TTF_Font		*f_status;
	char			quit;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define FONT_NAME	(window->f_names)
# define FONT_STAT	(window->f_status)
# define WIN_QUIT	(window->quit)

t_window		*visu_init_win(void);
void			win_events(t_window *window);
int				load_files(t_window *window);
#endif
