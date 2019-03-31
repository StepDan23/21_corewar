/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:36:29 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:36:30 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	wdth_fld_set(int c, int *i, t_fmt *fmts)
{
	int			it;
	char		fill;

	it = 1;
	fill = (ZO && !MS) ? ('0') : (' ');
	(MS) ? ft_printf_putchar(c, i, 1, fmts) : (0);
	while (it < WIDTH)
	{
		ft_printf_putchar(fill, i, 1, fmts);
		it++;
	}
	(!MS) ? ft_printf_putchar(c, i, 1, fmts) : (0);
}

static int	find_sps_sub(t_fmt *fmts, va_list ap, const char **curp, int *c_c)
{
	int			read_res;

	(*curp)++;
	if ((read_res = read_format_item(curp, ap, fmts)) == 1)
		select_type_group(fmts, ap, c_c);
	else if (read_res == 0)
		wdth_fld_set(**curp, c_c, fmts);
	else if (**curp == '\0')
		return (1);
	return (0);
}

static int	find_sps(const char *fmt, va_list ap, int c_c)
{
	t_fmt		*fmts;
	const char	*curp;

	curp = fmt;
	fmts = fmt_init('\0', NULL);
	while (*curp)
	{
		if (*curp == '%' && *(curp + 1) == '{')
			ft_printf_clr_chk(&curp);
		else if (*curp == '%' && *(curp + 1) != '%')
		{
			if ((find_sps_sub(fmts, ap, &curp, &c_c)) == 1)
				break ;
		}
		else
		{
			(*curp == '%' && *(curp + 1) == '%') ? (curp++) : 0;
			ft_printf_putchar(*curp, &c_c, 1, fmts);
		}
		curp++;
	}
	free(fmts->extra);
	free(fmts);
	return (c_c);
}

int			ft_printf(const char *fmt, ...)
{
	int		cntr;
	va_list ap;

	va_start(ap, fmt);
	cntr = find_sps(fmt, ap, 0);
	return (cntr);
}
