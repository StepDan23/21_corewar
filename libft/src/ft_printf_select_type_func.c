/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_select_type_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:41:05 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		select_fstrings(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	int c;

	if (fmts->type == 's' && !L1)
	{
		fmts->data = va_arg(ap, char*);
		ft_printf_putstr_s(fmts, ch_cntr);
	}
	else if (fmts->type == 'S' || (fmts->type == 's' && L1))
	{
		fmts->data = va_arg(ap, int*);
		ft_printf_widestr(fmts, ch_cntr);
	}
	else if (fmts->type == 'c' && !L1)
	{
		c = va_arg(ap, int);
		fmts->data = &c;
		ft_printf_putchar(*((char*)(fmts->data)), ch_cntr, fmts->width, fmts);
	}
	else
	{
		c = va_arg(ap, int);
		fmts->data = &c;
		ft_printf_widechar(*((int*)(fmts->data)), fmts, ch_cntr, PREC);
	}
}

void		select_fsig_dec(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	long long int c;

	if ((fmts->type == 'i' || fmts->type == 'd') && !L1 && !LL1
			&& !H1 && !HH1 && !J1 && !Z1)
		c = va_arg(ap, int);
	else if (fmts->type == 'D' || ((fmts->type == 'i' || fmts->type == 'd')
			&& L1 && !LL1 && !J1 && !Z1))
		c = va_arg(ap, long int);
	else if ((fmts->type == 'i' || fmts->type == 'd') && (LL1 || J1 || Z1))
		c = va_arg(ap, long long int);
	else if ((fmts->type == 'i' || fmts->type == 'd') && HH1 && !H1)
		c = (char)va_arg(ap, int);
	else if ((fmts->type == 'i' || fmts->type == 'd') && H1)
		c = (short)va_arg(ap, int);
	fmts->data = &c;
	ft_printf_putlld(fmts, ch_cntr);
}

void		select_funsig_dec(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	unsigned long long int c;

	if (fmts->type == 'u' && !L1 && !LL1 && !H1 && !HH1 && !J1 && !Z1)
		c = va_arg(ap, unsigned int);
	else if (fmts->type == 'U' || ((fmts->type == 'u') && L1
			&& !LL1 && !J1 && !Z1))
		c = va_arg(ap, unsigned long int);
	else if (fmts->type == 'u' && (LL1 || J1 || Z1))
		c = va_arg(ap, unsigned long long int);
	else if (fmts->type == 'u' && HH1 && !H1)
		c = (unsigned char)va_arg(ap, int);
	else if (fmts->type == 'u' && H1)
		c = (unsigned short)va_arg(ap, int);
	fmts->data = &c;
	ft_printf_putllu(fmts, ch_cntr);
}

void		select_hexoct(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	unsigned long long int c;

	if ((TYPE == 'x' || TYPE == 'o' || TYPE == 'X') && !L1 && !LL1 && !H1 &&
		!HH1 && !J1 && !Z1)
		c = va_arg(ap, unsigned int);
	else if (TYPE == 'O' || ((TYPE == 'x' || TYPE == 'o' || TYPE == 'X')
			&& L1 && !LL1 && !J1 && !Z1))
		c = va_arg(ap, unsigned long int);
	else if (LL1 || J1 || Z1)
		c = va_arg(ap, unsigned long long int);
	else if (HH1 && !H1)
		c = (unsigned char)va_arg(ap, int);
	else if (H1)
		c = (unsigned short)va_arg(ap, int);
	fmts->data = &c;
	if (fmts->type == 'x' || fmts->type == 'X')
		(fmts->type == 'x') ? ft_printf_putbase(fmts, ch_cntr, HEXBASE, 0) :
		ft_printf_putbase(fmts, ch_cntr, BIGHEXBASE, 1);
	else if (fmts->type == 'o' || fmts->type == 'O')
		(fmts->type == 'o') ? ft_printf_putbase(fmts, ch_cntr, OCTBASE, 0) :
		ft_printf_putbase(fmts, ch_cntr, OCTBASE, 1);
}
