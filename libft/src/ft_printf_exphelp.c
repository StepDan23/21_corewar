/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_exphelp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:36:20 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:36:22 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		g_exp = 0;
int		g_width = 0;
int		g_prec = 0;
int		g_len = 0;

char	*ft_add_exp_zeroes(char *str, int n, int len_first)
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

void	ft_mad_printer(t_fmt *fmts, char *ft, char *tale, int *i)
{
	g_width = ft_width_solver(fmts, tale, g_exp);
	g_prec = PREC;
	g_len = ft_strlen(tale);
	(SPC && !NEG && !PS) ? ft_printf_putchar(' ', i, -1, fmts) : 0;
	(NEG && (ZO || MS)) ? ft_printf_putchar('-', i, -1, fmts) : 0;
	(PS && !NEG && (ZO || MS)) ? ft_printf_putchar('+', i, -1, fmts) : 0;
	while (!MS && --g_width >= 0)
		ft_printf_putchar((ZO) ? '0' : ' ', i, -1, fmts);
	(NEG && !ZO && !MS) ? ft_printf_putchar('-', i, -1, fmts) : 0;
	(PS && !NEG && !ZO && !MS) ? ft_printf_putchar('+', i, -1, fmts) : 0;
	ft_printf_putchar(ft[0], i, -1, fmts);
	(HSH || PREC > 0) ? (ft_printf_putchar('.', i, -1, fmts)) : 0;
	PREC = -1;
	ft_printf_putstr(fmts, i);
	while (g_len++ < g_prec)
		ft_printf_putchar('0', i, -1, fmts);
	ft_printf_putchar((TYPE == 'E') ? 'E' : 'e', i, -1, fmts);
	ft_printf_putchar((g_exp < 0) ? '-' : '+', i, -1, fmts);
	g_exp = (g_exp < 0) ? (-g_exp) : (g_exp);
	(g_exp < 10) ? ft_printf_putchar('0', i, -1, fmts) :\
	(DATA = ft_itoa(g_exp));
	(g_exp < 10) ? ft_printf_putchar(g_exp + '0', i, -1, fmts) :\
	ft_printf_putstr(fmts, i);
	while (MS && --g_width >= 0)
		ft_printf_putchar(' ', i, -1, fmts);
}

char	*ft_round_round(t_fmt *fmts, char *ft, char *tale)
{
	int		temp;
	int		len1;
	int		j;

	len1 = ft_strlen(ft) - 1;
	if (PREC >= (int)ft_strlen(tale))
		return (ft);
	j = 1;
	temp = (tale[PREC - j + 1] - '0' >= 5) ? 1 : 0;
	while (PREC - j >= 0)
	{
		temp = tale[PREC - j] - '0' + temp;
		tale[PREC - j++] = temp % 10 + '0';
		temp = temp / 10;
	}
	j = 0;
	while (temp > 0 && j < len1 + 1)
	{
		temp = ft[len1 - j] - '0' + temp;
		ft[len1 - j++] = temp % 10 + '0';
		temp = temp / 10;
	}
	ft = (temp > 0) ? (ft_strjoin(ft_itoa(1), ft)) : ft;
	return (ft);
}

void	ft_pozitive(t_fmt *fmts, char *front, char *tale, int *i)
{
	int		len1;
	char	*ft;

	len1 = ft_strlen(front);
	ft = ft_itoa(front[0] - '0');
	tale = ft_strjoin(ft_strdup(&front[1]), tale);
	g_exp += len1 - 1;
	free(front);
	front = ft_round_round(fmts, ft, tale);
	(ft_strlen(front) > 1) ? ft_pozitive(fmts, front, tale, i) :\
	ft_mad_printer(fmts, front, tale, i);
}

void	ft_show_exp(t_fmt *fmts, char *front, char *tale, int *i)
{
	int		len1;
	int		j;
	char	*str;

	j = 0;
	tale = (tale[0] == 0) ? ft_strdup("000000") : tale;
	len1 = ft_strlen(front);
	if (len1 == 0 || (len1 == 1 && front[0] == '0'))
	{
		while (tale[j] == '0')
			j++;
		front = ft_itoa(tale[j] - '0');
		str = ft_strdup(&tale[j + 1]);
		free(tale);
		g_exp = -j - 1;
		front = ft_round_round(fmts, front, str);
		(ft_strlen(front) > 1) ? ft_pozitive(fmts, front, str, i) :\
		ft_mad_printer(fmts, front, str, i);
	}
	else
		ft_pozitive(fmts, front, tale, i);
}
