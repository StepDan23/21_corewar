/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:23:51 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 12:07:56 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	new_str = ft_strnew(len + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		new_str[i] = s[i];
		i++;
	}
	return (new_str);
}
