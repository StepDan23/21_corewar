/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putlld.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:36:05 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:36:06 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <inttypes.h>

static void	ft_printf_lld_support(t_fmt *fmts, long long n, int *w_c)
{
	int			int_len;

	fmts->flags = (ZO && PREC > -1) ? s_a_c(fmts->flags, 4, 4) : fmts->flags;
	int_len = (n == 0 && PREC == 0) ? (0) : ft_intlen(n);
	*w_c = (int_len >= WIDTH || MS) ? (int_len) : WIDTH;
	*w_c = (*w_c <= PREC) ? (PREC) : (*w_c);
}

static int	ft_printf_lld_subwrt(t_fmt *fmts, char *str, long long n)
{
	uintmax_t	k;
	int			j;

	k = (n < 0) ? ((-1) * (unsigned long long)n) : ((unsigned long long)n);
	j = 0;
	while (k > 0)
	{
		str[j++] = k % 10 + '0';
		k = k / 10;
	}
	(n == 0 && PREC != 0) ? (str[j++] = '0') : n;
	if (PREC > 0 && PREC > 0)
	{
		while (j < PREC)
			(str[j++] = '0');
		PREC = 0;
	}
	return (j);
}

void		ft_printf_putlld(t_fmt *fmts, int *i)
{
	int				j;
	long long		n;
	char			*str;
	char			fill;
	int				w_c;

	n = *((long long *)(DATA));
	fill = (ZO && PREC < 0) ? ('0') : (' ');
	ft_printf_lld_support(fmts, n, &w_c);
	(!(str = ft_strnew(w_c + 1))) ? exit(1) : NULL;
	j = ft_printf_lld_subwrt(fmts, str, n);
	(!PS && n >= 0 && !ZO && SPC) ? (str[j++] = ' ') : (1);
	(n < 0 && !MS && !ZO) ? (str[j++] = '-') : (1);
	(PS && n >= 0 && !ZO) ? (str[j++] = '+') : (1);
	(((n < 0 && (ZO || MS)) || (PS && n >= 0 && ZO) ||
		(!PS && n >= 0 && ZO && SPC)) ? w_c-- : (1));
	while (j < w_c)
		str[j++] = fill;
	(!PS && n >= 0 && ZO && SPC) ? (str[j++] = ' ') : (1);
	(PS && n >= 0 && ZO) ? (str[j++] = '+') : (1);
	((n < 0 && (ZO || MS))) ? (str[j++] = '-') : (1);
	ft_strrev(str);
	fmts->data = str;
	ft_printf_putstr(fmts, i);
	free(str);
}
