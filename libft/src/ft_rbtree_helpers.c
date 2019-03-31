/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:18:22 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/14 13:55:19 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			is_red(t_rbnode *node)
{
	return (node != NULL && node->red == 1);
}

/*
** функция для однократного поворота узла
*/

t_rbnode	*rb_single(t_rbnode *root, int dir)
{
	t_rbnode	*save;

	save = root->link[!dir];
	root->link[!dir] = save->link[dir];
	save->link[dir] = root;
	root->red = 1;
	save->red = 0;
	return (save);
}

/*
** функция для двукратного поворота узла
*/

t_rbnode	*rb_double(t_rbnode *root, int dir)
{
	root->link[!dir] = rb_single(root->link[!dir], !dir);
	return (rb_single(root, dir));
}

/*
**rn->red = 1; –инициализация красным цветом
*/

t_rbnode	*make_node(int data, char *text)
{
	t_rbnode	*rn;

	rn = (t_rbnode *)malloc(sizeof(*rn));
	if (rn != NULL)
	{
		rn->data = data;
		rn->red = 1;
		rn->text = text;
		rn->parent = NULL;
		rn->link[0] = NULL;
		rn->link[1] = NULL;
	}
	return (rn);
}

int			ft_first_elem(t_rbroot *tree, int data, char *text)
{
	tree->root = make_node(data, text);
	if (tree->root == NULL)
		exit(1);
	(tree->count)++;
	return (0);
}
