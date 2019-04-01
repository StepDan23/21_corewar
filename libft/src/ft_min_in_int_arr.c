/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_in_int_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:14:19 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/21 17:38:54 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min_in_int_arr(int *arr, int len)
{
	int		i;
	int		min;

	min = __INT_MAX__;
	i = 0;
	while (i < len)
	{
		if (arr[i] < min)
			min = arr[i];
		i++;
	}
	if (min == __INT_MAX__)
		min = (len == 0) ? __INT_MAX__ : arr[0];
	return (min);
}
