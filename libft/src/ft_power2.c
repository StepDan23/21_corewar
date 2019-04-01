/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:49:12 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_power2(int pw)
{
	char	*temp;

	if (pw >= 0 && pw < 63)
	{
		temp = ft_itoa(1LL << pw);
		if (!temp)
			exit(1);
		return (temp);
	}
	else
		return (ft_str_mult(ft_power2(pw / 2), ft_power2(pw - pw / 2)));
}
