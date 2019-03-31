/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putllu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:58:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <inttypes.h>

static char		*ft_printf_llu_supp(t_fmt *fmts, uintmax_t n, char fill)
{
	int			int_len;
	int			w_c;
	char		*str;
	int			j;

	int_len = (n == 0 && PREC == 0) ? (0) : ft_uintlen(n);
	w_c = (int_len >= WIDTH || MS) ? (int_len) : WIDTH;
	w_c = (w_c <= PREC) ? (PREC) : (w_c);
	(!(str = ft_strnew(w_c + 1))) ? exit(1) : NULL;
	j = 0;
	(n == 0 && PREC != 0) ? (str[j++] = '0') : n;
	while (n > 0)
	{
		str[j++] = n % 10 + '0';
		n = n / 10;
	}
	if (PREC > 0 && PREC > 0)
	{
		while (j < PREC)
			(str[j++] = '0');
		PREC = 0;
	}
	while (j < w_c)
		str[j++] = fill;
	return (str);
}

void			ft_printf_putllu(t_fmt *fmts, int *i)
{
	char			*str;
	char			fill;
	uintmax_t		n;

	n = *((uintmax_t*)(DATA));
	fill = (ZO && PREC < 0) ? ('0') : (' ');
	fmts->flags = (ZO && PREC > -1) ? s_a_c(fmts->flags, 4, 4) : fmts->flags;
	str = ft_printf_llu_supp(fmts, n, fill);
	ft_strrev(str);
	fmts->data = str;
	ft_printf_putstr(fmts, i);
	free(str);
}
