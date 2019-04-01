/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_addition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:20:08 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_str_addition(char *first, char *second)
{
	char	*res;
	int		len1;
	int		len2;
	int		temp;
	int		j;

	len1 = ft_strlen(first) - 1;
	len2 = ft_strlen(second) - 1;
	res = ft_strnew(((len1 > len2) ? len1 : len2) + 2);
	(res == NULL) ? (exit(1)) : 0;
	j = 0;
	temp = 0;
	while (temp > 0 || len1 - j >= 0 || len2 - j >= 0)
	{
		res[j] += temp;
		temp = res[j] + ((len1 - j >= 0) ? (first[len1 - j] - '0') : 0)\
		+ ((len2 - j >= 0) ? (second[len2 - j] - '0') : 0);
		res[j++] = temp % 10 + '0';
		temp = temp / 10;
	}
	ft_strrev(res);
	free(first);
	free(second);
	return (res);
}
