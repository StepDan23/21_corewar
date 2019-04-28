/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizasm_solve_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:54:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 20:13:00 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"
#include <stdlib.h>

void	ft_place_arg_value(t_machine *machine, int val, int fd_write, int flag)
{
	char	*str;

	if (flag == 1)
		ft_putchar_fd('r', fd_write);
	if (flag == 2)
		ft_putchar_fd(DIRECT_CHAR, fd_write);
	str = ft_itoa(val);
	ft_putstr_fd(str, fd_write);
	free(str);
}

void	ft_solve_arg3(t_machine *machine, int bite, int fd_write)
{
	static int	value = 0;
	static int	i = 0;

	if (i < M_ARG3_SIZE)
	{
		value += bite << (M_ARG3_SIZE - i - 1);
		if (++i == M_ARG3_SIZE)
		{
			ft_putchar_fd(' ', fd_write);
			ft_place_arg_value(machine, value, fd_write, M_ARG3);
			ft_putchar_fd('\n', fd_write);
			M_START_ROW = 1;
			value = 0;
			M_ARG3_SIZE = 0;
			i = 0;
		}
	}
}

void	ft_solve_arg2(t_machine *machine, int bite, int fd_write)
{
	static int	value = 0;
	static int	i = 0;

	if (i < M_ARG2_SIZE)
	{
		value += bite << (M_ARG2_SIZE - i - 1);
		if (++i == M_ARG2_SIZE)
		{
			ft_putchar_fd(' ', fd_write);
			ft_place_arg_value(machine, value, fd_write, M_ARG2);
			ft_putchar_fd((M_ARG3) ? SEPARATOR_CHAR : '\n', fd_write);
			M_START_ROW = 1;
			value = 0;
			M_ARG2_SIZE = 0;
			i = 0;
		}
		return ;
	}
	ft_solve_arg3(machine, bite, fd_write);
}

void	ft_solve_arg1(t_machine *machine, int bite, int fd_write)
{
	static int	value = 0;
	static int	i = 0;

	if (i < M_ARG1_SIZE)
	{
		value = bite << (M_ARG1_SIZE - i - 1);
		if (++i == M_ARG1_SIZE)
		{
			ft_place_arg_value(machine, value, fd_write, M_ARG1);
			ft_putchar_fd((M_ARG2) ? SEPARATOR_CHAR : '\n', fd_write);
			M_START_ROW = 1;
			value = 0;
			M_ARG1_SIZE = 0;
			i = 0;
		}
		return ;
	}
	ft_solve_arg2(machine, bite, fd_write);
}
