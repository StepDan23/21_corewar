/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_chain_in_linked_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:25:45 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 17:19:57 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_chain_in_linked_list(t_list *where, t_list *what)
{
	if (!where)
		where = what;
	else
		ft_lstadd_last(where, what);
}
