/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_mediana.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:24:14 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/02 17:03:50 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** заменил flag на !flag. Смотри внимательнее
*/

int			ft_arr_mediana(int *arr, int start, int len, int flag)
{
	int	*temp;
	int	i;
	int	med;

	temp = (int *)malloc(4 * (len + 1));
	if (temp == NULL)
		exit(1);
	i = -1;
	while (++i < len)
		temp[i] = arr[start + i];
	(!flag) ? ft_quicksort_lomuto_asc(temp, 0, i - 1) :\
	ft_quicksort_lomuto_des(temp, 0, i - 1);
	med = len / 2;
	med = temp[med];
	free(temp);
	return (med);
}
