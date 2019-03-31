/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:50:26 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_power_float(long x, long y)
{
	double	res;

	if (y > 0)
	{
		res = x;
		while (--y > 0)
			res = res * x;
		return (res);
	}
	else if (y < 0)
	{
		res = 1.0 / x;
		while (++y < 0)
			res = res / x;
	}
	else
		res = 1;
	return (res);
}
