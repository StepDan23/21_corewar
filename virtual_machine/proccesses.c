/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccesses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:07:50 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/02 20:02:25 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void		proccess_init_reg(unsigned int *reg)
{
	int	i;

	i = 0;
	while (i < REG_NUMBER)
	{
		reg[i] = 0;
		i++;
	}
}

t_proccess	*proccess_new(int player_id, int pos)
{
	t_proccess	*new_p;

	new_p = (t_proccess *)malloc(sizeof(t_proccess));
	if (!new_p)
		return (NULL);
	new_p->carry = 0;
	new_p->is_live = 0;
	new_p->player_id = player_id;
	new_p->position = pos;
	proccess_init_reg(new_p->registers);
	new_p->registers[0] = player_id;
	new_p->next = NULL;
	return (new_p);
}

void	proccess_add(t_proccess **head, t_proccess *new_p)
{
	if (head && new_p)
	{
		new_p->next = *head;
		*head = new_p;
	}
}
