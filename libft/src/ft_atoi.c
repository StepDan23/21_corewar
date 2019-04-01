/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:00:37 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_helper(const char *nptr, int i, long long res, int minus)
{
	long long	temp;

	if (nptr[i] == '-')
		minus = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		temp = res;
		if (temp * 10 / 10 != res && minus == 1)
			return (-1);
		if (temp * 10 / 10 != res && minus == -1)
			return (0);
		res = 10 * res + nptr[i++] - '0';
	}
	return ((int)(res) * minus);
}

int			ft_atoi(const char *nptr)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' ||\
	nptr[i] == '\f' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '\0')
		res = 0;
	else
		res = ft_helper(&(nptr[i]), 0, 0, 1);
	return (res);
}
