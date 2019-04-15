/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_root_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:22:42 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/11 10:05:12 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_rbroot	*ft_rbtree_root_init(void)
{
	t_rbroot	*root;

	root = (t_rbroot *)malloc(sizeof(t_rbroot));
	root->count = 0;
	root->root = 0;

	return(root);
}
