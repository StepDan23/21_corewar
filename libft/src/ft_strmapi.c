/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:26:30 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	new_str = (char *)malloc(ft_strlen(s) + 1);
	if (new_str == NULL)
		return (NULL);
	while (s[i])
	{
		if (!(new_str[i] = (*f)(i, s[i])))
		{
			return (NULL);
		}
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
