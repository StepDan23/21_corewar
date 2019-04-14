/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:05:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/04/14 17:33:03 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

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

static t_champion	**init_champs(int players_count)
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
		champ[i]->name = ft_strnew(40);
		champ[i]->last_live = 0;
		champ[i]->lives_in_period = 0;
		i++;
	}
	champ[i] = NULL;
	ft_strcpy(champ[0]->name, "SSSS");
	if (players_count > 1)
		ft_strcpy(champ[1]->name, "TWO_B");
	if (players_count > 2)
		ft_strcpy(champ[2]->name, "THREE_C");
	if (players_count > 3)
		ft_strcpy(champ[3]->name, "FOUR_D");
	return (champ);
}

static t_proccess	*init_proc(void)
{
	t_proccess	*proc;

	proc = (t_proccess*)malloc(sizeof(t_proccess));
	proc->position = 64;
	proc->player_id = 0;
	proc->cycles_to_wait = 10;
	proc->size_written = 2;
	proc->pos_written = 30 + 50;
	//
	proc->next = (t_proccess*)malloc(sizeof(t_proccess));
	proc->next->position = 128;
	proc->next->player_id = 1;
	proc->next->cycles_to_wait = 12;
	proc->next->size_written = 2;
	proc->next->pos_written = 60 + 50;
	//
	proc->next->next = (t_proccess*)malloc(sizeof(t_proccess));
	proc->next->next->position = 2200;
	proc->next->next->player_id = 2;
	proc->next->next->cycles_to_wait = 12;
	proc->next->next->size_written = 3;
	proc->next->next->pos_written = 90 + 50;
	//
	proc->next->next->next = (t_proccess*)malloc(sizeof(t_proccess));
	proc->next->next->next->position = 3300;
	proc->next->next->next->player_id = 3;
	proc->next->next->next->cycles_to_wait = 12;
	proc->next->next->next->size_written = 4;
	proc->next->next->next->pos_written = 120 + 50;
	//
	proc->next->next->next->next = (t_proccess*)malloc(sizeof(t_proccess));
	proc->next->next->next->next->position = 3000;
	proc->next->next->next->next->player_id = -1;
	proc->next->next->next->next->cycles_to_wait = 12;
	proc->next->next->next->next->next = NULL;
	return (proc);
}

static t_vm			*init_virtual_machine(void)
{
	t_vm			*vm;

	vm = (t_vm*)malloc(sizeof(t_vm));
	VM_CHAMP_COUNT = 4;
	ft_strcpy((char*)VM_MEMORY, "LOL KEK");
	VM_CHAMPS = init_champs(VM_CHAMP_COUNT);
	vm->process = init_proc();
	VM_CYCLE = 0;
	VM_CYCLE_TO_DIE = 100;
	VM_P_TOTAL = 0;
	return (vm);
}

int					main(void)
{
	t_window		*window;
	t_vm			*vm;

	if (!(window = init_win()))
		exit(0);
	if (!(vm = init_virtual_machine()))
		exit(0);
	if (load_files(window, vm) != 0)
		exit(0);
	make_back_arena(window, vm);
	while (!WIN_QUIT)
	{
	// SDL_RenderClear(WIN_REND);
		win_events(window);
		render_image(window, vm);
		SDL_RenderPresent(WIN_REND);
		// SDL_Delay(1);
	}
	visu_close(window);
}
