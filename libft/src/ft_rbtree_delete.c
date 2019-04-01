/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:34:52 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:35:40 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			g_dir;
t_rbnode	*g_p;
t_rbnode	*g_g;
t_rbnode	g_hed = {0};

static void	ft_changers(int data, t_rbnode **f, t_rbnode **q)
{
	g_g = g_p;
	g_p = (*q);
	(*q) = (*q)->link[g_dir];
	g_dir = (*q)->data < data;
	((*q)->data == data) ? *f = (*q) : 0;
}

static void	ft_opers(t_rbnode **s, int last)
{
	int		dir2;

	dir2 = (g_g->link[1] == g_p);
	if (is_red((*s)->link[last]))
		g_g->link[dir2] = rb_double((g_p), last);
	else if (is_red((*s)->link[!last]))
		g_g->link[dir2] = rb_single(g_p, last);
	g_g->link[dir2]->red = 1;
	g_g->red = g_g->link[dir2]->red;
	g_g->link[dir2]->link[0]->red = 0;
	g_g->link[dir2]->link[1]->red = 0;
}

static void	ft_help(int data, t_rbnode **q, t_rbnode **f, t_rbnode **s)
{
	int last;

	last = g_dir;
	ft_changers(data, f, q);
	if (!is_red(*q) && !is_red((*q)->link[g_dir]))
	{
		if (is_red((*q)->link[!g_dir]))
		{
			g_p->link[last] = rb_single((*q), g_dir);
			g_p = g_p->link[last];
		}
		else if (!is_red((*q)->link[!g_dir]))
		{
			(*s) = g_p->link[!last];
			if (*s)
			{
				if (!is_red((*s)->link[!last]) && !is_red((*s)->link[last]))
					ft_del_color_change(&g_p, s, q);
				else
					ft_opers(s, last);
			}
		}
	}
}

void		ft_rbtree_del(t_rbroot *tree, int data)
{
	t_rbnode *q;
	t_rbnode *f;
	t_rbnode *s;

	if (tree->root != NULL)
	{
		f = NULL;
		g_dir = 1;
		q = &g_hed;
		g_p = NULL;
		g_g = NULL;
		q->link[1] = tree->root;
		while (q->link[g_dir])
			ft_help(data, &q, &f, &s);
		(f) ? ft_del_remove_el(&f, &q, &g_p, &tree) : 0;
		tree->root = g_hed.link[1];
		(tree->root != NULL) ? tree->root->red = 0 : 0;
		ft_relationships(tree->root);
	}
}
