/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:41:01 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

/*
**31 (!PS && ZO && SPC) ? ft_printf_putchar(' ', i, -(WIDTH--), fmts) : (1);
**(PS && ZO) ? ft_printf_putchar('+', i, -(WIDTH--), fmts) : (1);
**(((PS && !ZO) || (!PS && !ZO && SPC)) ? length-- : (1));
**35(!PS && !ZO && SPC) ? ft_printf_putchar(' ', i, -(WIDTH--), fmts) : (1);
**(PS && !ZO) ? ft_printf_putchar('+', i, -(WIDTH--), fmts) : (1);
*/

static int		ft_printf_psub(t_fmt *fmts, int len, int *i, char fill)
{
	int		j;
	int		length;

	fmts->flags = (ZO && PREC > -1) ? s_a_c(fmts->flags, 4, 4) : fmts->flags;
	j = -1;
	length = WIDTH - ((PREC > 0 && PREC - len > 0) ? (PREC + 2) : (len + 2));
	while (!MS && (fill != '0') && ++j < length)
		ft_printf_putchar(fill, i, -1, fmts);
	return (j);
}

void			ft_printf_pointers(t_fmt *fmts, int *i)
{
	int					len;
	char				*str;
	int					j;
	char				fill;

	fill = (ZO && PREC < 0) ? ('0') : (' ');
	str = ft_base_convert("0123456789abcdef", (unsigned long)(DATA));
	len = (*str == '0' && PREC == 0) ? (0) : ft_strlen(str);
	j = ft_printf_psub(fmts, len, i, fill);
	ft_printf_putchar('0', i, 1, fmts);
	ft_printf_putchar('x', i, 1, fmts);
	WIDTH -= 2;
	while (!MS && (fill == '0') && ++j < WIDTH - len)
		ft_printf_putchar(fill, i, -1, fmts);
	str[0] = (PREC == 0 && *str == '0') ? ('\0') : (str[0]);
	fmts->data = str;
	ft_printf_putstr(fmts, i);
	free(str);
}
