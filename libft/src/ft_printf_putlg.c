/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putlg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:47:07 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			g_lgprec = 0;

static int	ft_counter(char *str, int j, int flag, t_fmt *fmts)
{
	int	res;

	res = 0;
	if (flag == 0)
		while (str[j] && j < PREC)
		{
			if (str[j] != '0')
				res = j + 1;
			j++;
		}
	if (flag == 1)
	{
		while (str[j] == '0')
			j++;
		res = j;
	}
	return (res);
}

void		ft_lsender(t_fmt *fmts, char *ft, char *tale, int *i)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(ft);
	ft = ft_round_round(fmts, ft_round_round(fmts, ft, tale), tale);
	len2 = ft_counter(tale, 0, 1, fmts);
	if (len1 > g_lgprec || (ft[0] == '0' && len2 >= 4))
	{
		PREC = PREC - 1;
		tale = (len1 > 1) ? (&ft[1]) : tale;
		PREC = ft_counter(tale, 0, 0, fmts);
		ft_printf_putlexp(fmts, i);
	}
	else
	{
		PREC = PREC - len1;
		PREC = ft_counter(tale, 0, 0, fmts) + ((ft[0] == '0') ? (len2 + 1) : 0);
		ft_printf_putldbl(fmts, i);
	}
}

void		ft_lggg_result(t_fmt *fmts, int ex, unsigned long long mant, int *i)
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
	ft_lsender(fmts, frnt, tale, i);
}

void		ft_printf_putlg(t_fmt *fmts, int *i)
{
	unsigned long long	mant;
	long long			ex;
	unsigned char		b[10];

	ft_memcpy(b, ((long double *)DATA), 10);
	ft_strrev_num(b, 10);
	mant = *((unsigned long long *)DATA);
	ex = ((b[0] << 8) + (b[1]));
	NEG = (ex & 32768) >> 15;
	ex = (ex & 32767) - 16383;
	g_lgprec = (PREC < 0) ? 6 : PREC;
	PREC = g_lgprec;
	ft_lggg_result(fmts, ex, mant, i);
}
