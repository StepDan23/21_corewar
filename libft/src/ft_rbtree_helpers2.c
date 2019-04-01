/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:03:08 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/02 17:03:10 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/*
** дедушка
** родитель
** родитель
** итератор
** временный корень дерева
*/

t_rbnode	*g_g;
t_rbnode	*g_p;
t_rbnode	*g_tt;
t_rbnode	*g_q;
t_rbnode	g_head = {0};
int			g_last;

void		ft_color_swap(t_rbnode *q)
{
	q->red = 1;
	q->link[0]->red = 0;
	q->link[1]->red = 0;
}

t_rbnode	*ft_insert_node(t_rbnode **g_q, int data, char *t, t_rbroot *tree)
{
	*g_q = make_node(data, t);
	if (*g_q == NULL)
		exit(1);
	(tree->count)++;
	return (*g_q);
}

void		rb_insert2(t_rbroot *tree, int data, char *text, int dir)
{
	g_last = 2;
	g_tt = &g_head;
	g_g = NULL;
	g_p = NULL;
	g_tt->link[1] = tree->root;
	g_q = tree->root;
	while (1)
	{
		if (g_q == NULL)
			g_p->link[dir] = ft_insert_node(&g_q, data, text, tree);
		else if (is_red(g_q->link[0]) && is_red(g_q->link[1]))
			ft_color_swap(g_q);
		if (is_red(g_q) && is_red(g_p))
			g_tt->link[g_tt->link[1] == g_g] = (g_q == g_p->link[g_last])\
			? rb_single(g_g, !g_last) : rb_double(g_g, !g_last);
		if (g_q->data == data)
			break ;
		g_last = dir;
		dir = g_q->data < data;
		(g_g != NULL) ? (g_tt = g_g) : 0;
		g_g = g_p;
		g_p = g_q;
		g_q = g_q->link[dir];
	}
	tree->root = g_head.link[1];
}

int			rb_insert(t_rbroot *tree, int data, char *text)
{
	int		dir;

	dir = 0;
	if (tree->root == NULL)
		ft_first_elem(tree, data, text);
	else
		rb_insert2(tree, data, text, dir);
	tree->root->red = 0;
	ft_relationships(tree->root);
	return (1);
}
