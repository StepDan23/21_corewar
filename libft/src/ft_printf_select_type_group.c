/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_select_type_group.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:23:23 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <stdlib.h>

void		select_type_group(t_fmt *fmts, va_list ap, int *ch_cntr)
{
	if (fmts->type == 's' || fmts->type == 'S' || fmts->type == 'c'
		|| fmts->type == 'C')
		select_fstrings(fmts, ap, ch_cntr);
	else if (fmts->type == 'd' || fmts->type == 'i' || fmts->type == 'D')
		select_fsig_dec(fmts, ap, ch_cntr);
	else if (fmts->type == 'u' || fmts->type == 'U')
		select_funsig_dec(fmts, ap, ch_cntr);
	else if (fmts->type == 'o' || fmts->type == 'O' || fmts->type == 'x'
		|| fmts->type == 'X')
		select_hexoct(fmts, ap, ch_cntr);
	else if (fmts->type == 'f' || fmts->type == 'F')
		select_fdoubles(fmts, ap, ch_cntr);
	else if (fmts->type == 'g' || fmts->type == 'G')
		select_fgs(fmts, ap, ch_cntr);
	else if (fmts->type == 'e' || fmts->type == 'E')
		select_fexpos(fmts, ap, ch_cntr);
	else if (fmts->type == 'p' || fmts->type == 'b' || fmts->type == 'r')
		select_fextras(fmts, ap, ch_cntr);
}
