/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_root_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:08:18 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 12:08:21 by lshanaha         ###   ########.fr       */
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

	return (root);
}
