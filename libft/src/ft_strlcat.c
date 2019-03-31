/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:52:07 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	res;

	res = ft_strlen((char *)src);
	res += ((size_t)ft_strlen(dst) < n ? (size_t)ft_strlen(dst) : n);
	while (*dst && n)
	{
		dst++;
		n--;
	}
	if (!n)
		return (res);
	while (--n && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (res);
}
