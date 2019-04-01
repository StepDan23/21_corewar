/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putbase.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:27:28 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <stdlib.h>
#include "libft.h"

static int		ft_putbase_precwr(t_fmt *fmts, size_t ns, char *str, int *i)
{
	int		length;
	int		len;
	int		j;
	int		fill;
	int		a;

	a = (ns == 8) ? (1) : (2);
	(HSH && ns == 8 && *str != '0') ? (PREC++) : (0);
	fill = (ZO && PREC < 0) ? ('0') : (' ');
	(HSH && ns == 8 && *str != '0') ? (PREC--) : (0);
	j = -1;
	len = (*str == '0' && PREC == 0) ? (0) : (ft_strlen(str));
	len += (*str == '0' && PREC == 0 && ns == 8 && HSH) ? (1) : (0);
	if (*str != '0')
		length = WIDTH - ((PREC > 0 && PREC - len > 0) ? (PREC) : (len)) -
			((HSH) ? (a) : (0));
	else
		length = WIDTH - ((PREC > 0 && PREC - len > 0) ? (PREC) : (len));
	while (!MS && (fill != '0') && ++j < length)
		ft_printf_putchar(fill, i, -1, fmts);
	return (j);
}

static void		ft_putbase_sub(t_fmt *fmts, int *i, size_t ns, int big)
{
	(ns == 16 || ns == 2) ? ft_printf_putchar('0', i, 0, fmts) : (1);
	(ns == 16 || ns == 2) ? WIDTH-- : (1);
	if (ns == 8)
		ft_printf_putchar('0', i, 0, fmts);
	else if (ns == 16)
		big ? ft_printf_putchar('X', i, 0, fmts) :
			ft_printf_putchar('x', i, 0, fmts);
	else if (ns == 2)
		big ? ft_printf_putchar('B', i, 0, fmts) :
			ft_printf_putchar('b', i, 0, fmts);
	(ns == 16 || ns == 2 || ns == 8) ? WIDTH-- : (1);
}

void			ft_printf_putbase(t_fmt *fmts, int *i, char *base, int big)
{
	char	*str;
	int		len;
	int		j;
	size_t	ns;
	char	fill;

	fill = (ZO && PREC < 0) ? ('0') : (' ');
	ns = ft_strlen(base);
	str = ft_base_convert(base, *((uintmax_t*)DATA));
	len = (*str == '0' && PREC == 0) ? (0) : (ft_strlen(str));
	len += (*str == '0' && PREC == 0 && ns == 8 && HSH) ? (1) : (0);
	(HSH && ns == 8 && *str != '0') ? (PREC--) : (0);
	j = ft_putbase_precwr(fmts, ns, str, i);
	if (HSH && (*str != '0' || (*str == '0' && ns == 8)))
		ft_putbase_sub(fmts, i, ns, big);
	while (!MS && (fill == '0') && ++j < WIDTH - len)
		ft_printf_putchar(fill, i, -1, fmts);
	str[0] = (((HSH && ns == 8) || PREC == 0) && *str == '0') ?
		('\0') : (str[0]);
	fmts->data = str;
	ft_printf_putstr(fmts, i);
	free(str);
}
