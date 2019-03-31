/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:49:01 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strrev_bin(char **str)
{
	int		i;
	int		len;
	int		temp;
	char	*new;
	int		j;

	len = ft_strlen(*str);
	ft_strrev(*str);
	temp = len;
	(len % 8 == 0) ? (len) : (len = (len / 8) * 8 + 8);
	i = -1;
	j = 0;
	if (len > temp)
	{
		(!(new = ft_strnew(len + len / 8))) ? exit(1) : new;
		while (++i < len - temp)
			new[i] = '0';
		while (i < len)
			new[i++] = (*str)[j++];
		*str = new;
	}
	return (*str);
}
