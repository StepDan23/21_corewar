/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccesses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:07:50 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/05 01:15:26 by artemiy          ###   ########.fr       */
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

t_proccess	*proccess_new(int id, int player_id, int pos)
{
	t_proccess	*new_p;

	new_p = (t_proccess *)malloc(sizeof(t_proccess));
	if (!new_p)
		return (NULL);
	new_p->id = id;
	new_p->carry = 0;
	new_p->is_live = 0;
	new_p->player_id = player_id;
	new_p->position = pos;
	proccess_init_reg(new_p->registers);
	new_p->registers[0] = player_id;
	new_p->next = NULL;
	new_p->cycles_to_wait = 0;
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

void	proccess_kill(t_proccess **head, t_proccess *ps)
{
	t_proccess	*prev;
	t_proccess	*curr;

	if (!head || !ps)
		return ;
	curr = *head;
	if (curr == ps)
	{
		(*head) = (*head)->next;
		free(curr);
		return ;
	}
	while (curr && curr != ps)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	free(curr);
}

/*
** Удаляет процессы у которых live = 0
*/

void	proccess_check_live(t_proccess **head)
{
	t_proccess	*curr;
	
	if (!head)
		return ;
	curr = *head;
	while (curr)
	{
		if (!curr->is_live)
			proccess_kill(head, curr);
		else
			curr->is_live = 0;
		curr = curr->next;
	}
}
