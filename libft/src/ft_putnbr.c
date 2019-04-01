/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:18:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr(int n)
{
	int				i;
	unsigned int	k;

	k = n;
	if (n < 0)
	{
		write(1, "-", 1);
		k = (unsigned int)n;
		k = (-1) * (k);
	}
	if (k >= 10)
		ft_putnbr(k / 10);
	i = k % 10 + '0';
	write(1, &i, 1);
}
