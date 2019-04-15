/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:02:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/12 20:42:13 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "vm.h"
#include "libft.h"

/*
** Считает кол-во чемпионов
*/

int		count_champs(t_champion **head)
{
	int			champs_num;

	champs_num = 0;
	while (head[champs_num])
		champs_num++;
	return (champs_num);
}

/*
** Записывает код чемпиона в память (vm->memory)
** index - адресс куда записать
*/

void	vm_load_champ(unsigned char *mem, t_champion *champ, int index)
{
	unsigned int	i;

	i = 0;
	while (i < champ->size)
	{
		mem[index + i] = champ->code[i];
		i++;
	}
}

/*
** Рассчитывает адресс для записи
** total - общее число чемпионов
** curr - порядковый номер чемпиона
*/

int		vm_index_to_load(int total, int curr)
{
	int	pos;

	pos = curr * (MEM_SIZE / total);
	// pos -= pos % 32;
	return (pos);
}

/*
** Распределяет чемпионов по памяти машины
** Создает по 1 процессу (каретке) на чемпиона
*/

void	vm_spread_champs(t_vm *vm, t_champion **champs)
{
	int			i;
	int			champs_num;
	t_proccess	*proccess;

	champs_num = count_champs(champs);
	i = 0;
	while (champs[i])
	{
		vm_load_champ(vm->memory, champs[i], vm_index_to_load(champs_num, i));
		proccess = proccess_new(i, champs[i]->id, vm_index_to_load(champs_num, i));
		if (!proccess)
		{
			ft_printf("Error: %s\n", strerror(errno));
			exit(0);
		}
		proccess_add(&vm->process, proccess);
		i++;
	}
}
