/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:52:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_printf_putstr_s(t_fmt *fmts, int *i)
{
	int		len;
	int		j;
	char	*str;

	str = (char*)(DATA);
	if (str == NULL)
	{
		str = "(null)";
	}
	len = ft_strlen(str);
	len = (PREC > -1 && PREC < len) ? (fmts->precision) : (len);
	j = 0;
	while (!MS && WIDTH-- - len > 0)
		ft_printf_putchar((ZO) ? '0' : ' ', i, 0, fmts);
	if (PREC > -1)
		while (j < len)
			ft_printf_putchar(str[j++], i, 0, fmts);
	else
		while (str[j])
			ft_printf_putchar(str[j++], i, 0, fmts);
	while (WIDTH-- - j > 0 && MS)
		ft_printf_putchar(' ', i, 0, fmts);
}

void	ft_printf_putstr(t_fmt *fmts, int *i)
{
	int		len;
	int		j;
	char	*str;
	int		w_c;

	w_c = WIDTH;
	str = (char*)(fmts->data);
	len = ft_strlen(str);
	j = 0;
	if (PREC > 0 && PREC - len > 0)
	{
		j = -1;
		while (++j < PREC - len)
			ft_printf_putchar('0', i, -1, fmts);
		w_c -= j;
	}
	j = 0;
	while (str[j])
		ft_printf_putchar(str[j++], i, 0, fmts);
	w_c -= j;
	while (w_c > 0 && MS)
	{
		ft_printf_putchar(' ', i, 0, fmts);
		w_c--;
	}
}
