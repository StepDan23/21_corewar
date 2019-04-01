/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:23:17 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_insert(t_btree **r, void *item, int (*cmpf)(void *, void *))
{
	t_btree *node;

	if (cmpf == NULL || r == NULL || item == NULL)
		return ;
	if ((*r) == NULL)
		*r = ft_btree_create_node(item);
	node = *r;
	if (cmpf(node->data, item) > 0)
	{
		if (node->left == NULL)
			node->left = ft_btree_create_node(item);
		else
			ft_btree_insert(&(node->left), item, (cmpf));
	}
	if (cmpf(node->data, item) < 0)
	{
		if (node->right == NULL)
			node->right = ft_btree_create_node(item);
		else
			ft_btree_insert(&(node->right), item, (cmpf));
	}
}
