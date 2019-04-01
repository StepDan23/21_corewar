/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_solver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:28:11 by lshanaha          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_width_solver(t_fmt *fmts, char *tale, int g_exp)
{
	int		len;
	int		temp;

	len = ft_intlen(g_exp);
	WIDTH = WIDTH - 3;
	WIDTH -= (PREC == 0) ? 0 : (PREC + 1);
	WIDTH -= (HSH && PREC == 0) ? 1 : 0;
	WIDTH -= (PS || SPC || NEG);
	WIDTH -= (len <= 2) ? 2 : len;
	tale[PREC] = '\0';
	DATA = tale;
	temp = WIDTH;
	WIDTH = 0;
	return (temp);
}
