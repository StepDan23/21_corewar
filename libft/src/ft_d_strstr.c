/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_strstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:43:05 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/12 14:54:31 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_d_strstr(const char *str, const char *needle, char stop_symbol)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != stop_symbol)
	{
		if (str[i] == needle[0])
		{
			j = 0;
			while (needle[j] && (str[i + j] == needle[j]))
				j++;
			if (!needle[j])
				return (i);
		}
		i++;
	}
	return (-1);
}
