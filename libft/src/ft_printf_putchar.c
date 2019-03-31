/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:53:13 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_help(int fd, const void *buf)
{
	(*((char*)buf) == 24) ? write(fd, "'CAN'", 5) : 0;
	(*((char*)buf) == 25) ? write(fd, "'EOM'", 5) : 0;
	(*((char*)buf) == 26) ? write(fd, "'SUB'", 5) : 0;
	(*((char*)buf) == 27) ? write(fd, "'ESC'", 5) : 0;
	(*((char*)buf) == 28) ? write(fd, "'FSP'", 5) : 0;
	(*((char*)buf) == 29) ? write(fd, "'GSP'", 5) : 0;
	(*((char*)buf) == 30) ? write(fd, "'ESP'", 5) : 0;
	(*((char*)buf) == 31) ? write(fd, "'USP'", 5) : 0;
	return ((*((char*)buf) <= 31 ? (5) : (write(1, ((char*)buf), 1))));
}

static int	write_unprint(int fd, const void *buf)
{
	(*((char*)buf) == 0) ? write(fd, "'NUL'", 5) : 0;
	(*((char*)buf) == 1) ? write(fd, "'SOH'", 5) : 0;
	(*((char*)buf) == 2) ? write(fd, "'STX'", 5) : 0;
	(*((char*)buf) == 3) ? write(fd, "'ETX'", 5) : 0;
	(*((char*)buf) == 4) ? write(fd, "'EOT'", 5) : 0;
	(*((char*)buf) == 5) ? write(fd, "'ENQ'", 5) : 0;
	(*((char*)buf) == 6) ? write(fd, "'ACK'", 5) : 0;
	(*((char*)buf) == 7) ? write(fd, "'BEL'", 5) : 0;
	(*((char*)buf) == 8) ? write(fd, "'BCS'", 5) : 0;
	(*((char*)buf) == 9) ? write(fd, "'TAB'", 5) : 0;
	(*((char*)buf) == 10) ? write(fd, "'NLF'", 5) : 0;
	(*((char*)buf) == 11) ? write(fd, "'VTB'", 5) : 0;
	(*((char*)buf) == 12) ? write(fd, "'NPF'", 5) : 0;
	(*((char*)buf) == 13) ? write(fd, "'CRR'", 5) : 0;
	(*((char*)buf) == 14) ? write(fd, "'SHO'", 5) : 0;
	(*((char*)buf) == 15) ? write(fd, "'SHI'", 5) : 0;
	(*((char*)buf) == 16) ? write(fd, "'DLE'", 5) : 0;
	(*((char*)buf) == 17) ? write(fd, "'DC1'", 5) : 0;
	(*((char*)buf) == 18) ? write(fd, "'DC2'", 5) : 0;
	(*((char*)buf) == 19) ? write(fd, "'DC3'", 5) : 0;
	(*((char*)buf) == 20) ? write(fd, "'DC4'", 5) : 0;
	(*((char*)buf) == 21) ? write(fd, "'NAK'", 5) : 0;
	(*((char*)buf) == 22) ? write(fd, "'SYN'", 5) : 0;
	(*((char*)buf) == 23) ? write(fd, "'ETB'", 5) : 0;
	return ((*((char*)buf) <= 23) ? (5) : ft_help(fd, buf));
}

int			write_st(int fd, const void *buf, size_t n, t_cntrl *cns)
{
	int			cntr;

	cntr = 0;
	while (n--)
	{
		if (cns && cns->type == 's')
		{
			((char*)(cns->data))[cns->data_size++] = *(char*)buf;
			cntr++;
		}
		else if (cns && cns->type == 'f')
			cntr += write(*((int*)(cns->data)), buf, 1);
		else if (cns && cns->type == 'r')
			cntr += write_unprint(fd, buf);
		else
			cntr += write(fd, buf, 1);
		buf++;
	}
	return (cntr);
}

void		ft_printf_putchar(int c, int *i, int width, t_fmt *fmts)
{
	int		j;
	t_cntrl *cns;

	cns = (t_cntrl*)(fmts->extra);
	j = 0;
	c = c % 256;
	while (!MS && width - j++ > 1)
		*i += write_st(1, (ZO) ? ("0") : " ", 1, cns);
	*i += write_st(1, &c, 1, cns);
	while (MS && width - j++ > 1)
		*i += write_st(1, " ", 1, cns);
}
