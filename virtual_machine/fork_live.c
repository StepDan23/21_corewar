/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:39:26 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/12 20:45:45 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
**	fork
**	Операция fork делает копию каретки. 
**	И эту копию размещает по адресу <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD
*/

void	ft_fork(t_vm *vm, t_proccess *proccess)
{
	int	value;
	int	i;

	value = get_2bytes(vm->memory,(P_POS + 1) % MEM_SIZE) % IDX_MOD;
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, get_realtive_addr(P_POS, value)));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	P_POS = (P_POS + 2) % MEM_SIZE;
	vm->p_total++;
	vm->p_num[P_PI]++;
}

/*
**	lfork
**	По своей сути эта операция аналогична операции fork.
**	
**	За исключением того факта, что новая каретка в этом случае
**	создается по адресу — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ>.
**	В операции lfork усечение по модулю делать не нужно.
*/

void	lfork(t_vm *vm, t_proccess *proccess)
{
	int	index;
	int	i;

	index = get_2bytes(vm->memory,(P_POS + 1) % MEM_SIZE);
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, get_realtive_addr(P_POS, index)));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	P_POS = (P_POS + 2) % MEM_SIZE;
	vm->p_total++;
	vm->p_num[P_PI]++;
}

/*
**	live
**	Она засчитывает, что каретка, которая выполняет операцию live, жива.
**	
**	Если указанный в качестве аргумента операции live номер совпадает
**	с номером игрока, то она засчитывает, что это игрок жив. Например,
**	если значение аргумента равно -2, значит игрок с номером 2 жив.
*/

void	live(t_vm *vm, t_proccess *proccess)
{
	int			number;
	t_champion	**players;
	int			i;

	number = get_4bytes(vm->memory, (P_POS + 1) % MEM_SIZE);
	proccess->is_live = 1;
	vm->live_exec++;
	players = vm->champion;
	i = 0;
	while (players[i])
	{
		if (players[i]->id == -number)
		{
			vm->winner = players[i];
			players[i]->lives_in_period++;
			players[i]->last_live = vm->cycles;
		}
		i++;
	}
	P_POS = (P_POS + 4) % MEM_SIZE;
}

void	aff(t_vm *vm, t_proccess *proccess)
{
	char	ch;

	ch = (char)P_REG[get_4bytes(vm->memory, (P_POS + 2) % MEM_SIZE) - 1];
	ft_printf("%c", ch);
}

