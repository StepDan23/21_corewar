/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_performe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:26:48 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/04 00:37:40 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	performe_proc(t_vm *vm, t_proccess *head, t_op op_tab[17])
{
	while (head)
	{
		if (!head->cycles_to_wait)
		{
			head->command_type = vm->memory[head->position];
			if (head->command_type < 17 && head->command_type > 0)
				head->cycles_to_wait = op_tab[head->command_type]->cycles_to_wait;
		}
		if (head->cycles_to_wait > 0)
			head->cycles_to_wait--;
		if (!head->cycles_to_wait)
		{
			if (head->command_type < 17 && head->command_type > 0)
			{
				ft_printf("%s", op_tab[head->command_type]->name);
			}
			else
				head->position++;			
		}
	}
}
