/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:36:49 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:36:50 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_bubble_sort(int *arr, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
** int main(void)
** {
** 	int	*a;
** 	int	i;
** 	a = malloc(4 * 20);
** 	if (a == NULL)
** 		return (0);
** 	i = -1;
** 	while (++i < 20)
** 		a[i] = i + 1;
** 	i = -1;
** 	while (++i < 20)
** 		ft_printf("%d ", a[i]);
** 	ft_printf("\n");
** 	ft_bubble_sort(a, 20);
** 	i = -1;
** 	while (++i < 20)
** 		ft_printf("%d ", a[i]);
** 	ft_printf("\n");
** 	return (0);
** }
*/
