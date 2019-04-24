/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:16:43 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/21 20:57:01 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_base_convert(char *base_str, unsigned long long nbr)
{
	char	*result;
	int		base_num;
	int		i;

	base_num = ft_strlen(base_str);
	result = ft_strnew(256 / base_num);
	i = 0;
	if (nbr == 0)
		result[i] = '0';
	while (nbr != 0)
	{
		result[i] = base_str[nbr % base_num];
		nbr = nbr / base_num;
		i++;
	}
	(base_num == 2) ? (ft_strrev_bin(&result)) : (ft_strrev(result));
	return (result);
}

char	*ft_int_base_convert(char *base_str, unsigned int nbr)
{
	char	*result;
	int		base_num;
	int		i;

	base_num = ft_strlen(base_str);
	result = ft_strnew(256 / base_num);
	i = 0;
	if (nbr == 0)
		result[i] = '0';
	while (nbr != 0)
	{
		result[i] = base_str[nbr % base_num];
		nbr = nbr / base_num;
		i++;
	}
	(base_num == 2) ? (ft_strrev_bin(&result)) : (ft_strrev(result));
	return (result);
}
