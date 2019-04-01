/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_format_item.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:35:51 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/28 18:35:52 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

static int		read_fmt_check(const char **str_p, t_fmt *fmt, va_list ap)
{
	if (**str_p == '.')
	{
		if (*(*str_p + 1) == '*' && fmt_varg_len_set(&(fmt->precision), ap))
			*str_p += 2;
		else
			*str_p = fmt_read_numbers(&(fmt->precision), *str_p + 1);
	}
	else if (fmt_flag_set(&(fmt->flags), **str_p))
		(*str_p)++;
	else if (**str_p >= '0' && **str_p <= '9')
		*str_p = fmt_read_numbers(&(fmt->width), *str_p);
	else if (fmt_size_set(&(fmt->size), str_p))
		(*str_p)++;
	else if (**str_p == '*' && fmt_varg_len_set(&(fmt->width), ap))
	{
		(fmt->width < 0) ? (fmt->flags = set_bit(fmt->flags, 0)) : (0);
		(fmt->width < 0) ? (fmt->width = ABS(fmt->width)) : (0);
		(*str_p)++;
	}
	else if (fmt_type_set(&(fmt->type), **str_p))
		return (0);
	else
		return (-1);
	return (1);
}

int				read_format_item(const char **str_p, va_list ap, t_fmt *fmt)
{
	int		err;

	fmt_clear(fmt);
	err = 0;
	while (**str_p != '\0')
	{
		err = read_fmt_check(str_p, fmt, ap);
		if (err == 0)
			return (1);
		else if (err == -1)
			return (0);
	}
	return (-1);
}
