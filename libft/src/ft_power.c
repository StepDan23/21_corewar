/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:49:03 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_power(long x, long y)
{
	long long	res;

	if (y > 0)
	{
		res = x;
		while (--y > 0)
			res = res * x;
		return (res);
	}
	else
		res = 1;
	return (res);
}
