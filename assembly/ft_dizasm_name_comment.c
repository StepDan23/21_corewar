/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizasm_name_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:51:36 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 20:01:23 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"

void	ft_solve_comment(t_machine *machine, int bite, int fd_write)
{
	static int	i = 0;

	if (M_COMMENT)
	{
		ft_dizasm_comment(fd_write);
		(bite > 0) ? ft_putchar_fd(bite, fd_write) : 0;
		i++;
		if (i == COMMENT_LENGTH)
		{
			M_COMMENT = 0;
			M_SECOND_NULL = 1;
			ft_putstr_fd("\"\n\n", fd_write);
		}
		return ;
	}
	ft_solve_second_null(machine, bite, fd_write);
}

void	ft_solve_size(t_machine *machine, int bite, int fd_write)
{
	static int	i = 0;

	if (M_SIZE)
	{
		i++;
		if (i == 4)
		{
			M_SIZE = 0;
			M_COMMENT = 1;
		}
		return ;
	}
	ft_solve_comment(machine, bite, fd_write);
}

void	ft_solve_first_null(t_machine *machine, int bite, int fd_write)
{
	static int	i = 0;

	if (M_FIRST_NULL)
	{
		i++;
		if (i == 4)
		{
			M_FIRST_NULL = 0;
			M_SIZE = 1;
		}
		return ;
	}
	ft_solve_size(machine, bite, fd_write);
}

void	ft_solve_name(t_machine *machine, int bite, int fd_write)
{
	static int	i = 0;

	if (M_NAME)
	{
		ft_dizasm_name(fd_write);
		(bite > 0) ? ft_putchar_fd(bite, fd_write) : 0;
		i++;
		if (i == PROG_NAME_LENGTH)
		{
			M_NAME = 0;
			M_FIRST_NULL = 1;
			ft_putstr_fd("\"\n", fd_write);
		}
		return ;
	}
	ft_solve_first_null(machine, bite, fd_write);
}

void	ft_solve_header(t_machine *machine, int value, int fd_write)
{
	static int		i = 0;

	if (M_HEADER)
	{
		i++;
		if (i == 4)
		{
			M_HEADER = 0;
			M_NAME = 1;
		}
		return ;
	}
	ft_solve_name(machine, value, fd_write);
}
