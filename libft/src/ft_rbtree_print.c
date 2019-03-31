/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:03:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/02 17:40:41 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_rbtree_print(t_rbnode *p)
{
	if (p != NULL && p->text != NULL)
	{
		ft_rbtree_print(p->link[0]);
		ft_putstr_fd(p->text, 1);
		ft_rbtree_print(p->link[1]);
	}
}
