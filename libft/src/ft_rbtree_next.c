/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:14:57 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 17:15:13 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbnode		*ft_rbtree_next(t_rbroot *root, int data)
{
	int			i;
	t_rbnode	*max;
	t_rbnode	*next;

	if (root == NULL || root->root == NULL)
		return (0);
	i = data;
	next = NULL;
	max = root->root;
	while (max->link[1])
		max = max->link[1];
	while (i < max->data)
	{
		next = ft_rbtree_datasearch(root, i + 1);
		if (next && next->text)
			break ;
		i++;
	}
	return (next);
}
