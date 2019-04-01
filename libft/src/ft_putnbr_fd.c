/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:19:50 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				i;
	unsigned int	k;

	if (fd < 0)
		return ;
	k = (unsigned int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		k = (unsigned int)n;
		k = (-1) * k;
	}
	if (k >= 10)
		ft_putnbr_fd(k / 10, fd);
	i = k % 10 + '0';
	write(fd, &i, 1);
}
