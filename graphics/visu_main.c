/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/13 19:16:13 by mmcclure         ###   ########.fr       */
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

static void			get_player_color(t_window *window, t_vm *vm, int i)
{
	if (i >= 0 && i < VM_CHAMPS[0]->size)
		FONT_COLOR = (SDL_Color){COL_GREEN};
	else if (i >= (4096 / VM_CHAMP_COUNT) &&
			i < (4096 / VM_CHAMP_COUNT + VM_CHAMPS[1]->size) && VM_CHAMP_COUNT > 1)
		FONT_COLOR = (SDL_Color){COL_BLUE};
	else if (i >= (2 * 4096 / VM_CHAMP_COUNT) &&
			i < (2 * 4096 / VM_CHAMP_COUNT + VM_CHAMPS[2]->size) && VM_CHAMP_COUNT > 2)
		FONT_COLOR = (SDL_Color){COL_RED};
	else if (i >= (3 * 4096 / VM_CHAMP_COUNT) &&
			i < (3 * 4096 / VM_CHAMP_COUNT + VM_CHAMPS[3]->size) && VM_CHAMP_COUNT > 3)
		FONT_COLOR = (SDL_Color){COL_YELOW};
	else
		FONT_COLOR = (SDL_Color){COL_L_GREY};
}

static void			init_back_arena(t_window *window, t_vm *vm)
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
			get_player_color(window, vm, j * 64 + i);
			str[0] = hex[VM_MEMORY[j * 64 + i] / 16];
			str[1] = hex[VM_MEMORY[j * 64 + i] % 16];
			str[2] = '\0';
			print_str(window, str, 13 + 18.7 * i, 20 + 13.5 * j);
			i++;
		}
		j++;
	}
	SDL_SetRenderTarget(WIN_REND, NULL);
	FONT_COLOR = (SDL_Color){COL_WHITE};
}

static t_champion			**init_champs(unsigned char	*first_state, int players_count)
{
	t_champion		**champ;
	int				i;

	champ = (t_champion**)malloc(sizeof(t_champion*) * (players_count + 1));
	i = 0;
	while (i < players_count)
	{
		champ[i] = (t_champion*)malloc(sizeof(t_champion));
		champ[i]->id = i;
		champ[i]->size = 23 + i * 23;
		champ[i]->name = ft_strnew(10);
		champ[i]->last_live = 0;
		champ[i]->lives_in_period = 0;
		i++;
	}
	champ[i] = NULL;
	ft_strcpy(champ[0]->name, "ONE_A");
	ft_strcpy(champ[1]->name, "TWO_B");
	ft_strcpy(champ[2]->name, "THREE_C");
	ft_strcpy(champ[3]->name, "FOUR_D");
	return(champ);
}

static t_proccess		*init_proc()
{
	t_proccess	*proc;

	proc = (t_proccess*)malloc(sizeof(t_proccess));
	proc->position = 64;
	proc->player_id = 0;
	proc->cycles_to_wait = 10;
	proc->next = (t_proccess*)malloc(sizeof(t_proccess));
	proc->next->position = 80;
	proc->next->player_id = 1;
	proc->next->cycles_to_wait = 12;
	proc->next->next = NULL;
	return(proc);
}

static t_vm				*init_virtual_machine(void)
{
	t_vm			*vm;

	vm = (t_vm*)malloc(sizeof(t_vm));
	VM_CHAMP_COUNT = 4;
	ft_strcpy((char*)VM_MEMORY, "LOL KEK");
	VM_CHAMPS = init_champs(VM_MEMORY, VM_CHAMP_COUNT);
	vm->process = init_proc();
	VM_CYCLE = 0;
	VM_CYCLE_TO_DIE = 100;
	VM_P_TOTAL = 0;
	return (vm);
}

int				main(void)
{
	t_window		*window;
	t_vm			*vm;


	if (!(window = init_win()))
		exit(0);
	if (!(vm = init_virtual_machine()))
		exit(0);
	if (load_files(window, vm) != 0)
		exit(0);
	init_back_arena(window, vm);
	while (!WIN_QUIT)
	{
		// SDL_RenderClear(WIN_REND);
		win_events(window);
		render_image(window,vm);
		SDL_RenderPresent(WIN_REND);
		// SDL_Delay(1);
	}
	visu_close(window);
}
