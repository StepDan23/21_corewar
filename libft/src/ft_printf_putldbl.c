/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putldbl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:33:05 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_ldbl_result(t_fmt *fmts, int ex, unsigned long long mant, int *i)
{
	char	*tale;
	char	*frnt;
	int		power;

	(!(tale = ft_strdup("000000")) ? (exit(1)) : 0);
	(!(frnt = ft_strdup("0"))) ? (exit(1)) : 0;
	power = -(-63 + ex);
	while (ex - 63 < 0 && mant > 0)
	{
		if (mant & 1)
			tale = ft_str_addition(tale, ft_add_zeroes(\
			ft_power5(-(ex - 63)), -(ex - 63), power));
		mant = mant >> 1;
		ex++;
	}
	while (mant > 0)
	{
		if (mant & 1)
			frnt = ft_str_addition(frnt, ft_power2(ex - 63));
		mant = mant >> 1;
		ex++;
	}
	(MS) ? (WIDTH--) : (0);
	ft_show_result(fmts, frnt, tale, i);
}

int		ft_check_vals(t_fmt *fmts, int e, unsigned long long m, int *i)
{
	if (e != 16384 && e != -16383)
		return (1);
	if (e == -16383)
		ft_show_result(fmts, ft_strdup("0"), ft_strdup("000000"), i);
	PREC = 0;
	fmts->flags = fmts->flags & ((m == 9223372036854775808ULL) ? 7 : 1);
	if (e != -16383 && m == 9223372036854775808ULL)
		ft_show_result(fmts, ft_strdup((TYPE == 'E' || TYPE == 'G')\
		? ("INF") : ("inf")), ft_strnew(0), i);
	else if (e != -16383)
		ft_show_result(fmts, ft_strdup((TYPE == 'E' || TYPE == 'G')\
		? ("NAN") : ("nan")), ft_strnew(0), i);
	return (0);
}

void	ft_printf_putldbl(t_fmt *fmts, int *i)
{
	unsigned long long	mant;
	long long			ex;
	unsigned char		b[10];

	ft_memcpy(b, ((long double *)DATA), 10);
	ft_strrev_num(b, 10);
	mant = *((unsigned long long *)DATA);
	ex = ((b[0] << 8) + (b[1]));
	NEG = (ex & 32768) >> 15;
	if (ex > 32767)
	{
		DATA = (double *)(DATA);
		ft_printf_putdbl(fmts, i);
		return ;
	}
	ex = (ex & 32767) - 16383;
	PREC = (PREC < 0) ? (6) : PREC;
	(ft_check_vals(fmts, ex, mant, i)) ? ft_ldbl_result(fmts, ex, mant, i) : 0;
}
