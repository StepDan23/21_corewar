/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_select_type_func_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:10:31 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		select_fdoubles(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	double		c;
	long double	lc;

	if ((fmts->type == 'f' || fmts->type == 'F') && !L)
	{
		c = va_arg(ap, double);
		fmts->data = &c;
		ft_printf_putdbl(fmts, ch_cntr);
	}
	else if ((fmts->type == 'f' || fmts->type == 'F') && L)
	{
		lc = va_arg(ap, long double);
		fmts->data = &lc;
		ft_printf_putldbl(fmts, ch_cntr);
	}
}

void		select_fextras(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	unsigned long long int c;

	if (fmts->type == 'p')
	{
		fmts->data = va_arg(ap, void*);
		ft_printf_pointers(fmts, ch_cntr);
	}
	else if (fmts->type == 'b')
	{
		c = va_arg(ap, unsigned long long int);
		fmts->data = &c;
		ft_printf_putbase(fmts, ch_cntr, BINBASE, 0);
	}
	else if (fmts->type == 'r')
		(((t_cntrl*)(fmts->extra))->type == '\0') ?
			(((t_cntrl*)(fmts->extra))->type = 'r') : (1);
}

void		select_fexpos(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	double		c;
	long double	lc;

	if ((fmts->type == 'e' || fmts->type == 'E') && !L)
	{
		c = va_arg(ap, double);
		fmts->data = &c;
		ft_printf_putexp(fmts, ch_cntr);
	}
	else if ((fmts->type == 'e' || fmts->type == 'E') && L)
	{
		lc = va_arg(ap, long double);
		fmts->data = &lc;
		ft_printf_putlexp(fmts, ch_cntr);
	}
}

void		select_fgs(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	double		c;
	long double	lc;

	if ((fmts->type == 'g' || fmts->type == 'G') && !L)
	{
		c = va_arg(ap, double);
		fmts->data = &c;
		ft_printf_putg(fmts, ch_cntr);
	}
	else if ((fmts->type == 'g' || fmts->type == 'G') && L)
	{
		lc = va_arg(ap, long double);
		fmts->data = &lc;
		ft_printf_putlg(fmts, ch_cntr);
	}
}
