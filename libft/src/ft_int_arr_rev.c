/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_arr_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:36:44 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:36:45 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_int_arr_rev(int *arr, int len)
{
	int	temp;
	int	j;

	j = 0;
	while (j < len - j)
	{
		temp = arr[j];
		arr[j] = arr[len - j];
		arr[len - j] = temp;
		j++;
	}
}
