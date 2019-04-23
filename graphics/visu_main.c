/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/22 17:15:43 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void			visu_close(t_window *window)
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

int					main(int argc, char **argv)
{
	t_window		*window;
	t_vm			*vm;
	t_op			op_tab[17];

	if (!(vm = init_vm_test(argc, argv)))
		exit(0);
	if (!(window = init_win(vm)))
		exit(0);
	if (load_files(window, vm) != 0)
		exit(0);
	make_background(window, vm);
	init_optab(op_tab);
init_tests(vm);
	while (WIN_STATUS != STAT_QUIT)
	{
		if (vm->end_game)
			WIN_STATUS = STAT_END;
		render_image(window, vm, op_tab);
		SDL_RenderPresent(WIN_REND);
		win_events(window);
	}
	visu_close(window);
}
