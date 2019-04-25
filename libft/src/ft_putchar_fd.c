/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:07:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:01:17 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(unsigned char c, int fd)
{
	unsigned char q;
	unsigned char z;

	if (fd < 0)
		return ;
	if (c < 0)
	{
		q = 256 + c;
		z = q;
		q = q & 0xbf;
		z = (((z >> 6) & 0x1f) | (0xc0));
		write(fd, &z, 1);
		write(fd, &q, 1);
	}
	else
		write(fd, &c, 1);
}
