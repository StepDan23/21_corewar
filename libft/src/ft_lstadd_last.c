/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:21:12 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 19:39:56 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_last(t_list *alst, t_list *new)
{
	if (new == NULL || alst == NULL)
		return ;
	if (alst == NULL)
	{
		new->next = NULL;
		alst = new;
	}
	else
	{
		while ((alst)->next)
			(alst) = (alst)->next;
		(alst)->next = new;
	}
}
