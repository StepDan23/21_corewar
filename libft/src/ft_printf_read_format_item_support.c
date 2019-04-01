/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_format_item_support.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 00:04:32 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_cntrl	*cntrl_init(char type, void *data)
{
	t_cntrl		*new_cntrl;

	if (!(new_cntrl = (t_cntrl*)malloc(sizeof(t_cntrl))))
		exit(0);
	new_cntrl->type = type;
	new_cntrl->data = data;
	new_cntrl->data_size = 0;
	new_cntrl->neg = 0;
	return (new_cntrl);
}

void			fmt_clear(t_fmt *fmt_struct)
{
	fmt_struct->flags = 0;
	fmt_struct->width = 0;
	fmt_struct->precision = -1;
	fmt_struct->size = 0;
	fmt_struct->type = 0;
	fmt_struct->data = NULL;
}

t_fmt			*fmt_init(char type, void *data)
{
	t_fmt *fmt_struct;

	if (!(fmt_struct = (t_fmt*)malloc(sizeof(t_fmt))))
		exit(0);
	fmt_struct->extra = cntrl_init(type, data);
	fmt_clear(fmt_struct);
	return (fmt_struct);
}

char			set_bit(char bte, char num)
{
	return (bte | (1 << num));
}

char			s_a_c(char fmts, char whereset, char whereclr)
{
	fmts = set_bit(fmts, whereset);
	fmts = fmts & ~(1 << whereclr);
	return (fmts);
}
