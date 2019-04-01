/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:55:10 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	size_t i;
	size_t j;

	if (!(*sub))
		return ((char *)str);
	i = 0;
	if ((n < ft_strlen(sub)) && (ft_strlen(str)))
		return (NULL);
	while (str[i] && (i <= n - ft_strlen(sub)))
	{
		if (str[i] == sub[0])
		{
			j = 0;
			while (sub[j] && (str[i + j] == sub[j]) && j < n)
				j++;
			if (!sub[j] || (j == n))
				return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}
