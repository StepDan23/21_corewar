/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:56:41 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 18:32:53 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static long long	ft_helper(const char *nptr, int i, long long res, int minus)
{
	long long	temp;

	if (nptr[i] == '-')
		minus = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		temp = res;
		res = 10 * res + nptr[i++] - '0';
		if (temp > res)
			return (-1000000);
	}
	return ((res) * minus);
}

long long			ft_atol(const char *nptr)
{
	int			i;
	long long	res;

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
