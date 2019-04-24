/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:48:42 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 13:34:32 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_helper(char *new_str)
{
	new_str[0] = '0';
	return (new_str);
}

char		*ft_itoa(long long n)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!(new_str = ft_strnew((n == 0) ? 1 : ft_intlen(n))))
		return (NULL);
	if (n == 0)
		return (ft_helper(new_str));
	if (n < 0)
	{
		new_str[i++] = -(n % 10) + '0';
		n = n / 10;
		j = -1;
		n = j * n;
	}
	(n != 0) ? (new_str[i++] = n % 10 + '0') : (n);
	while ((n = (n / 10)))
		(new_str[i++]) = n % 10 + '0';
	if (j == -1)
		(new_str[i++]) = '-';
	new_str[i] = '\0';
	ft_strrev(new_str);
	return (new_str);
}
