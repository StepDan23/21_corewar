/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:20:44 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_mult_one(char *str, int c, int zero)
{
	char	*res;
	int		len;
	int		j;
	int		temp;

	len = ft_strlen(str) - 1;
	res = ft_strnew(len + zero + 2);
	(res == NULL) ? (exit(1)) : 0;
	j = 0;
	temp = 0;
	while (j < zero)
		res[j++] = '0';
	while (temp > 0 || len + zero - j >= 0)
	{
		res[j] += temp;
		temp = ((len + zero - j >= 0)\
		? (str[len + zero - j] - '0') : 0) * c + res[j];
		res[j] = temp % 10 + '0';
		temp = temp / 10;
		j++;
	}
	ft_strrev(res);
	return (res);
}

char	*ft_str_mult(char *first, char *second)
{
	char	*res;
	char	*temp;
	int		len2;
	int		j;

	len2 = ft_strlen(second) - 1;
	res = ft_strdup("0");
	(res == NULL) ? (exit(1)) : 0;
	j = 0;
	while (len2 - j >= 0)
	{
		temp = ft_mult_one(first, second[len2 - j] - '0', j);
		res = ft_str_addition(res, temp);
		j++;
	}
	free(first);
	free(second);
	return (res);
}
