/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render_carrier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:36:36 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/17 11:32:42 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		make_carr_color(t_window *window, t_proccess *proc)
{
	unsigned char	id;

	id = window->mem_code[proc->position];
	FONT_COLOR = (SDL_Color){COL_BLACK};
	if (id > 4)
	{
		id = id % 5;
		FONT_COLOR = (SDL_Color){COL_L_GREY};
	}
	if (id == 0)
	{
		FONT_COLOR = (SDL_Color){COL_GREY};
		SDL_SetRenderDrawColor(WIN_REND, COL_L_GREY);
	}
	else if (id == 1)
		SDL_SetRenderDrawColor(WIN_REND, COL_GREEN);
	else if (id == 2)
		SDL_SetRenderDrawColor(WIN_REND, COL_BLUE);
	else if (id == 3)
		SDL_SetRenderDrawColor(WIN_REND, COL_RED);
	else if (id == 4)
		SDL_SetRenderDrawColor(WIN_REND, COL_YELOW);
}

void			render_carrier(t_window *window, t_vm *vm)
{
	SDL_Rect	rect;
	t_proccess	*proc;
	int			pos;
	char		str[3];
	char		*hex;

	hex = "0123456789abcdef";
	proc = vm->process;
	str[2] = '\0';
	FONT_CURR = FONT_ARENA;
	while (proc)
	{
		pos = proc->position;
		rect = (SDL_Rect){13 + pos % 64 * 18.7,
							20 + 13.5 * (int)(pos / 64), 15, 15};
		make_carr_color(window, proc);
		SDL_RenderFillRect(WIN_REND, &rect);
		str[0] = hex[VM_MEMORY[pos] / 16];
		str[1] = hex[VM_MEMORY[pos] % 16];
		print_str(window, str, 13 + pos % 64 * 18.7,
							20 + 13.5 * (int)(pos / 64));
		proc = proc->next;
	}
}

static void		render_source_back(t_window *window, t_vm *vm, int id, int pos)
{
	char		*hex;
	char		str[3];
	SDL_Rect	rect;

	hex = "0123456789abcdef";
	FONT_COLOR = get_player_color(id);
	MEM_CODE[pos] = id;
	rect = (SDL_Rect){13 + pos % 64 * 18.7,
				20 + 13.5 * (int)(pos / 64), 15, 15};
	SDL_RenderFillRect(WIN_REND, &rect);
	str[0] = hex[VM_MEMORY[pos] / 16];
	str[1] = hex[VM_MEMORY[pos] % 16];
	str[2] = '\0';
	print_str(window, str, 13 + pos % 64 * 18.7,
						20 + 13.5 * (int)(pos / 64));
}

void			render_carrier_source(t_window *window, t_vm *vm)
{
	t_proccess	*proc;
	int			i;

	SDL_SetRenderTarget(WIN_REND, WIN_BACK);
	SDL_SetRenderDrawColor(WIN_REND, COL_GREY);
	proc = vm->process;
	FONT_CURR = FONT_ARENA;
	i = -1;
	while (++i < MEM_SIZE)
		if (MEM_CODE[i] > 5)
		{
			MEM_CODE[i] -= 5;
			if (MEM_CODE[i] < 5)
				render_source_back(window, vm, MEM_CODE[i], i);
		}
	while (proc)
	{
		i = -1;
		if (proc->pos_written >= 0)
			while (++i < 4)
				render_source_back(window, vm,
							proc->player_id + 250, proc->pos_written + i);
		proc = proc->next;
	}
	SDL_SetRenderTarget(WIN_REND, NULL);
}
