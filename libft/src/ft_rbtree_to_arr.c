/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_to_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:13:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:02:05 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_rbtree_to_arr(t_rbnode *node, char **arr, int i)
{
	if (node->link[0])
		i = ft_rbtree_to_arr(node->link[0], arr, i);
	arr[i++] = node->text;
	if (node->link[1])
		i = ft_rbtree_to_arr(node->link[1], arr, i);
	return (i);
}

int		ft_rbtree_max(t_rbnode *node)
{
	int		temp;

	temp = 0;
	while (node->link[1])
		node = node->link[1];
	if (node)
		temp = node->data;
	return (temp);
}

int		ft_rbtree_min(t_rbnode *node)
{
	int		temp;

	temp = 0;
	while (node->link[0])
		node = node->link[0];
	if (node)
		temp = node->data;
	return (temp);
}

void	ft_rb_freetree(t_rbnode *node)
{
	if (node)
	{
		if (node->link[0])
			ft_rb_freetree(node->link[0]);
		if (node->link[1])
			ft_rb_freetree(node->link[1]);
		free(node);
	}
}
