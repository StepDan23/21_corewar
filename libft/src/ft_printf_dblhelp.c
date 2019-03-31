/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dblhelp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:54:06 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			g_dw = 0;
int			g_pr = 0;
int			g_tmp = 0;

char		*ft_add_zeroes(char *str, int n, int len_first)
{
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (len < len_first)
	{
		ft_strrev(str);
		res = ft_strnew(((n > len_first) ? n : len_first + 100) + 5);
		ft_memcpy(res, str, len);
		free(str);
		while (len < n)
			res[len++] = '0';
		ft_strrev(res);
		len = ft_strlen(res);
		while (len < len_first)
			res[len++] = '0';
		str = res;
	}
	return (str);
}

void		ft_dbl_print(t_fmt *fmts, char *ft, char *tl, int *i)
{
	(SPC && !NEG && !PS) ? ft_printf_putchar(' ', i, -1, fmts) : 0;
	(NEG && (ZO || MS)) ? ft_printf_putchar('-', i, -1, fmts) : 0;
	(PS && !NEG && (ZO || MS)) ? ft_printf_putchar('+', i, -1, fmts) : 0;
	while (!MS && --g_dw >= 0)
		ft_printf_putchar((ZO) ? '0' : ' ', i, -1, fmts);
	(NEG && !ZO && !MS) ? ft_printf_putchar('-', i, -1, fmts) : (DATA = ft);
	(PS && !NEG && !ZO && !MS) ? ft_printf_putchar('+', i, -1, fmts) :\
	(DATA = ft);
	ft_printf_putstr(fmts, i);
	(HSH || (g_tmp >= 0 && g_pr > 0))\
	? (ft_printf_putchar('.', i, -1, fmts)) : 0;
	DATA = tl;
	ft_printf_putstr(fmts, i);
	while (g_pr++ < g_tmp)
		ft_printf_putchar('0', i, -1, fmts);
	while (MS && --g_dw >= 0)
		ft_printf_putchar(' ', i, -1, fmts);
}

void		ft_dbl_width(t_fmt *fmts, char *front, char *tale)
{
	WIDTH -= ft_strlen(front);
	WIDTH -= (PREC == 0) ? 0 : (PREC + 1);
	WIDTH -= (HSH && PREC == 0) ? 1 : 0;
	WIDTH -= (PS || NEG || SPC);
	tale[PREC] = '\0';
	g_dw = WIDTH;
	WIDTH = 0;
	g_pr = ft_strlen(tale);
	g_tmp = PREC - g_pr;
	PREC = 0;
}

void		ft_show_result(t_fmt *fmts, char *front, char *tale, int *i)
{
	front = (front[0] == 0) ? (ft_strdup("0")) : (front);
	tale = (tale[0] == 0) ? (ft_strdup("000000")) : tale;
	front = ft_round_round(fmts, front, tale);
	ft_dbl_width(fmts, front, tale);
	ft_dbl_print(fmts, front, tale, i);
}
