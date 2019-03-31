/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:03:10 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *dest_st;
	unsigned char *src_st;

	dest_st = (unsigned char *)dest;
	src_st = (unsigned char *)src;
	while (n--)
	{
		*dest_st = *src_st;
		dest_st++;
		if (*src_st == (unsigned char)c)
			return ((void *)dest_st);
		src_st++;
	}
	if (dest == src)
		return (dest);
	return (NULL);
}
