/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:23:52 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			g_gprec = 0;

static int		ft_counter(char *str, int j, int flag, t_fmt *fmts)
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

void			ft_sender(t_fmt *fmts, char *ft, char *tale, int *i)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(ft);
	ft = ft_round_round(fmts, ft_round_round(fmts, ft, tale), tale);
	len2 = ft_counter(tale, 0, 1, fmts);
	if (len1 > g_gprec || (ft[0] == '0' && len2 >= 4))
	{
		PREC = PREC - 1;
		tale = (len1 > 1) ? (&ft[1]) : tale;
		PREC = ft_counter(tale, 0, 0, fmts);
		ft_printf_putexp(fmts, i);
	}
	else
	{
		PREC = PREC - len1;
		PREC = ft_counter(tale, 0, 0, fmts) + ((ft[0] == '0') ? (len2 + 1) : 0);
		ft_printf_putdbl(fmts, i);
	}
}

void			ft_ggg_result(t_fmt *fmts, int ex, unsigned long long mant,\
int *i)
{
	char	*tale;
	char	*front;
	int		power;

	(!(tale = ft_strdup("000000")) ? (exit(1)) : 0);
	(!(front = ft_strdup("0"))) ? (exit(1)) : 0;
	power = -(-52 + ex);
	while (ex - 52 < 0 && mant > 0)
	{
		if (mant & 1)
			tale = ft_str_addition(tale, ft_add_zeroes(\
			ft_power5(-(ex - 52)), -(ex - 52), power));
		mant = mant >> 1;
		ex++;
	}
	while (mant > 0)
	{
		if (mant & 1)
			front = ft_str_addition(front, ft_power2(ex - 52));
		mant = mant >> 1;
		ex++;
	}
	ft_sender(fmts, front, tale, i);
}

void			ft_printf_putg(t_fmt *fmts, int *i)
{
	unsigned long long	res;
	unsigned long long	mant;
	long long			ex;
	unsigned char		b[8];

	mant = 0;
	res = 0;
	ft_memcpy(b, ((double *)DATA), sizeof(double));
	ft_strrev_num(b, sizeof(double));
	while (mant < 8)
		res = (res << 8) + (b[mant++] % 256);
	NEG = (res & 0x8000000000000000) >> 63;
	res = res & 0x7FFFFFFFFFFFFFFF;
	ex = ((res & 0x7FF0000000000000) >> 52) - 1023;
	mant = (res & 0xfffffffffffff) | 0x10000000000000;
	g_gprec = (PREC < 0) ? 6 : PREC;
	PREC = g_gprec;
	ft_ggg_result(fmts, ex, mant, i);
}
