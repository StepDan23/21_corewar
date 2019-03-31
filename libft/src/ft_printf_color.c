/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:52:10 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int		clr_ch(const char *str, size_t size)
{
	int e;

	e = 0;
	if (size == 3)
	{
		e += (!ft_strcmp(str, ESCCLR)) ? (write(1, "\x1b[0m", 4)) : (0);
		e += (!ft_strcmp(str, REDCLR)) ? (write(1, "\x1b[31m", 5)) : (0);
	}
	else if (size == 4)
	{
		e += (!ft_strcmp(str, BLUECLR)) ? (write(1, "\x1b[34m", 5)) : (0);
		e += (!ft_strcmp(str, CYANCLR)) ? (write(1, "\x1b[36m", 5)) : (0);
	}
	else if (size == 5)
	{
		e += (!ft_strcmp(str, BLACKCLR)) ? (write(1, "\x1b[30m", 5)) : (0);
		e += (!ft_strcmp(str, GREENCLR)) ? (write(1, "\x1b[32m", 5)) : (0);
		e += (!ft_strcmp(str, WHITECLR)) ? (write(1, "\x1b[37m", 5)) : (0);
	}
	else if (size == 6)
		e += (!ft_strcmp(str, YELLOWCLR)) ? (write(1, "\x1b[33m", 5)) : (0);
	else
		e += (!ft_strcmp(str, MAGENTACLR)) ? (write(1, "\x1b[35m", 5)) : (0);
	return (e);
}

void			ft_printf_clr_chk(const char **str)
{
	const char		*str_head;
	char			*clr;
	char			*clr_head;
	size_t			cntr;

	str_head = *str + 2;
	if (!(clr = ft_strnew(7)))
		exit(0);
	clr_head = clr;
	cntr = 0;
	while (*str_head && *str_head != '}' && cntr < 7)
	{
		*clr = *str_head;
		cntr++;
		clr++;
		str_head++;
	}
	if (*str_head != '}' || cntr < 3 || cntr >= 7 || !clr_ch(clr_head, cntr))
	{
		free(clr_head);
		return ;
	}
	free(clr_head);
	*str = str_head;
}
