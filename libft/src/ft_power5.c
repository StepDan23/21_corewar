/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:49:45 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_power5(int power)
{
	char	*temp;

	if (power >= 0 && power < 28)
	{
		temp = ft_itoa(ft_power(5, power));
		if (!temp)
			exit(1);
		return (temp);
	}
	else
		return (ft_str_mult(ft_power5(power / 2),\
		ft_power5(power - power / 2)));
}
