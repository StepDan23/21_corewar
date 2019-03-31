/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_widestr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:51:35 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int g_nul[7] = {'(', 'n', 'u', 'l', 'l', ')', 0};

static int	ft_printf_strlen(int *str)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (*str)
	{
		(str[j] < 256) ? (len++) : (len);
		(str[j] >= 256 && str[j] < 2048) ? (len += 2) : len;
		(str[j] >= 2048 && str[j] < 65536) ? (len += 3) : len;
		(str[j] >= 65536) ? (len += 4) : len;
		str++;
	}
	return (len);
}

static int	ft_widechar_length(int c)
{
	int		res;

	res = 0;
	(c >= 256 && c < 2048) ? (res += 1) : res;
	(c >= 2048 && c < 65536) ? (res += 2) : res;
	(c >= 65536) ? (res += 3) : res;
	res++;
	return (res);
}

static int	ft_nbr_of_symbs(int *str, int len, t_fmt *fmts)
{
	int		i;
	int		j;
	int		res;
	int		temp;

	i = 0;
	res = -1;
	j = 0;
	temp = len;
	while (i < len && str[j])
	{
		if (len - i < ft_widechar_length(str[j]))
			break ;
		i += ft_widechar_length(str[j]);
		res++;
		j++;
	}
	while (res >= 0)
		temp -= ft_widechar_length(str[res--]);
	WIDTH += temp;
	return (res);
}

void		ft_printf_widestr(t_fmt *fmts, int *i)
{
	int		len;
	int		k;
	int		*str;

	str = (int*)(DATA);
	if (DATA == NULL)
		str = g_nul;
	len = ft_printf_strlen(str);
	len = (PREC > -1 && PREC < len) ? (PREC) : (len);
	ft_nbr_of_symbs(str, len, fmts);
	while (!MS && WIDTH - len > 0)
		ft_printf_putchar((ZO) ? '0' : ' ', i, -(WIDTH--), fmts);
	k = 0;
	while (k < len && *str)
	{
		if (len - k < ft_widechar_length(*str))
			return ;
		ft_printf_widechar(*str, fmts, i, len - k);
		k += ft_widechar_length(*str);
		str++;
	}
	while (MS && WIDTH - len > 0)
		ft_printf_putchar(' ', i, -(WIDTH--), fmts);
}
