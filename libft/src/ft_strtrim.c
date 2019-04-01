/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:36:13 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_free_arr(void)
{
	char	*arr;

	arr = (char *)malloc(1);
	if (arr == NULL)
		return (NULL);
	arr[0] = '\0';
	return (arr);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_str;

	if (s == 0x0)
		return (0);
	len = ft_strlen(s) - 1;
	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (i == len + 1)
		return (ft_free_arr());
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
		len--;
	new_str = (char *)malloc(len + 1 - i + 1);
	if (new_str == 0x0)
		return (0x0);
	while (s[i] && i <= len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}
