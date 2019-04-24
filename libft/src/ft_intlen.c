/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:13:37 by lshanaha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/18 19:54:11 by ttreutel         ###   ########.fr       */
=======
/*   Updated: 2019/04/24 13:34:02 by lshanaha         ###   ########.fr       */
>>>>>>> asm_branch
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**if (n <= 0)
**	i++;
*/

int		ft_intlen(long long n)
{
	int		i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int		ft_uintlen(unsigned long long n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
