/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_widechar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:51:59 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** c - символ, i - количество распечатанных символов, к-сколько байт распечатать
** по дефолту к = 4
*/
#include "libft.h"

static void	ft_helper(unsigned int c, t_fmt *fmts, int *i, int k)
{
	(k > 0 && c < 256) ? ft_printf_putchar(c, i, 0, fmts) : c;
	if (k > 0 && c >= 256 && c < 2048)
	{
		ft_printf_putchar(((c & 0x7C0) >> 6) | 0xC0, i, 0, fmts);
		k--;
	}
	else if (k > 0 && c >= 2048 && c < 65536)
	{
		ft_printf_putchar(((c & 0xF000) >> 12) | 0xE0, i, 0, fmts);
		k--;
	}
	else if (k > 0 && c >= 65536 && c <= 2097151)
	{
		ft_printf_putchar(((c & 0x1c0000) >> 18) | 0xF0, i, 0, fmts);
		k--;
		if (k-- > 0)
			ft_printf_putchar(((c & 0x3F000) >> 12) | 0x80, i, 0, fmts);
	}
	if (k > 0 && c >= 2048)
	{
		ft_printf_putchar((c & 0xFC0) >> 6 | 0x80, i, 0, fmts);
		k--;
	}
	if (k > 0 && c >= 256)
		ft_printf_putchar((c & 0x3F) | 0x80, i, 0, fmts);
}

void		ft_printf_widechar(unsigned int c, t_fmt *fmts, int *i, int k)
{
	k = (k < 0) ? (4) : k;
	if (PREC == 0)
	{
		if (c == 0)
		{
			ft_printf_putchar('\x00', i, 0, fmts);
			return ;
		}
	}
	ft_helper(c, fmts, i, k);
}
