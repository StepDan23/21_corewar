/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:39:26 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/24 15:05:03 by fkuhn            ###   ########.fr       */
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

	value = get_2bytes(vm->memory, (P_POS + 1) % MEM_SIZE) % IDX_MOD;
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, get_realtive_addr(P_POS, value)));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	vm->process->last_live = proccess->last_live;
	P_POS = (P_POS + 3) % MEM_SIZE;
	vm->p_total++;
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

	index = get_2bytes(vm->memory, (P_POS + 1) % MEM_SIZE);
	proccess_add(&vm->process,\
	proccess_new(vm->process->id + 1, P_PI, get_realtive_addr(P_POS, index)));
	i = 0;
	while (i < REG_NUMBER)
	{
		vm->process->registers[i] = P_REG[i];
		i++;
	}
	vm->process->carry = P_C;
	vm->process->last_live = proccess->last_live;
	P_POS = (P_POS + 3) % MEM_SIZE;
	vm->p_total++;
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

	number = get_4bytes(vm->memory, (P_POS + 1) % MEM_SIZE);
	proccess->last_live = vm->cycles;
	vm->live_exec++;
	players = vm->champion;
	if (-number > 0 && -number <= vm->champion_count)
	{
		vm->winner = players[-number - 1];
		players[-number - 1]->lives_in_period++;
		players[-number - 1]->last_live = vm->cycles;
		if ((vm->bit_flags & 1))
			ft_printf("A process shows that player %d (%s) is alive\n",
								-number, players[-number - 1]->name);
	}
	P_POS = (P_POS + 5) % MEM_SIZE;
}

void	aff(t_vm *vm, t_proccess *proccess)
{
	char	ch;
	int		reg_id;

	reg_id = vm->memory[(P_POS + 2) % MEM_SIZE] - 1;
	ch = (char)P_REG[reg_id];
	ft_printf("%c", ch);
}

/*
**	zjmp
**	Эта та самая функция, на работу которой влияет значение флага carry.
**
**	Если оно равно 1, то функция обновляет значение PC
**	на адрес — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**
**	То есть zjmp устанавливает куда должна переместиться каретка
**	для выполнения следующей операции. Это позволяет нам
**	перепрыгивать в памяти на нужную позицию, а не выполнять всё по порядку.
**
**	Если значение carry равно нулю, перемещение не выполняется.
*/

void	zjmp(t_vm *vm, t_proccess *proccess)
{
	int	value;

	if (P_C)
	{
		value = get_2bytes(vm->memory, (P_POS + 1) % MEM_SIZE) % IDX_MOD;
		P_POS = get_realtive_addr(P_POS, value);
	}
	else
		P_POS = (P_POS + 3) % MEM_SIZE;
}
