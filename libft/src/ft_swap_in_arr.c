/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_in_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:06:22 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/16 18:06:36 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_swap_in_arr(int **arr, int a, int b)
{
	int temp;

	if (a == b)
		return (a);
	temp = (*arr)[a];
	(*arr)[a] = (*arr)[b];
	(*arr)[b] = temp;
	return (a);
}
