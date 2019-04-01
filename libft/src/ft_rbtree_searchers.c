/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_searchers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:02:27 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 17:13:43 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_rbnode	*ft_rbtree_datasearch(t_rbroot *root, int data)
{
	t_rbnode	*res;

	res = root->root;
	while (res != NULL && res->data != data)
	{
		res = res->link[data > res->data];
	}
	return (res);
}

t_rbnode	*ft_rbtree_textsearch(t_rbnode *node, char *text)
{
	if (node->link[0])
		return (ft_rbtree_textsearch(node->link[0], text));
	if (node->link[1])
		return (ft_rbtree_textsearch(node->link[1], text));
	if (!ft_strcmp(node->text, text))
		return (node);
	else
		return (0);
}

void		ft_del_color_change(t_rbnode **p, t_rbnode **s, t_rbnode **q)
{
	(*p)->red = 0;
	(*s)->red = 1;
	(*q)->red = 1;
}

void		ft_del_remove_el(t_rbnode **f, t_rbnode **q, t_rbnode **p,\
t_rbroot **r)
{
	(*f)->data = (*q)->data;
	(*f)->text = (*q)->text;
	(*p)->link[(*p)->link[1] == (*q)] = (*q)->link[(*q)->link[0] == NULL];
	(*r)->count -= 1;
	free(*q);
}

void		ft_relationships(t_rbnode *parent)
{
	if (parent->link[0])
		parent->link[0]->parent = parent;
	if (parent->link[1])
		parent->link[1]->parent = parent;
	if (parent->link[0])
		ft_relationships(parent->link[0]);
	if (parent->link[1])
		ft_relationships(parent->link[1]);
}
