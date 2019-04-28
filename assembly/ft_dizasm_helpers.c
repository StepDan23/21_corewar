/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizasm_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:52:30 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 20:13:43 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"

void	ft_dizasm_name(int fd_write)
{
	static int	flag = 0;

	if (!flag)
	{
		ft_putstr_fd(NAME_CMD_STRING, fd_write);
		ft_putstr_fd(" \"", fd_write);
		flag = 1;
	}
}

void	ft_dizasm_comment(int fd_write)
{
	static int	flag = 0;

	if (!flag)
	{
		ft_putstr_fd(COMMENT_CMD_STRING, fd_write);
		ft_putstr_fd(" \"", fd_write);
		flag = 1;
	}
}

void	ft_solve_arg_types(t_machine *machine, int bite, int fd_write,\
int command)
{
	static int	command_types = 0;

	if (M_TYPE_SET)
	{
		if (M_TYPE_BITE)
			command_types = bite;
		else
		{
			command_types = 128;
			M_TYPE_SET = 0;
		}
		M_ARG1 = (command_types & 192) >> 6;
		M_ARG2 = (command_types & 48) >> 4;
		M_ARG3 = (command_types & 12) >> 2;
		M_ARG1_SIZE = ft_size_of_arg(machine, M_ARG1, command);
		M_ARG2_SIZE = ft_size_of_arg(machine, M_ARG2, command);
		M_ARG3_SIZE = ft_size_of_arg(machine, M_ARG3, command);
		if (M_TYPE_SET)
		{
			M_TYPE_SET = 0;
			return ;
		}
	}
	ft_solve_arg1(machine, bite, fd_write);
}

void	ft_solve_second_null(t_machine *machine, int bite, int fd_write)
{
	static int	i = 0;

	if (M_SECOND_NULL)
	{
		i++;
		if (i == 4)
		{
			M_SECOND_NULL = 0;
			M_CHAMP_CODE = 1;
			M_START_ROW = 1;
		}
		return ;
	}
	if (M_CHAMP_CODE)
		ft_solve_code(machine, bite, fd_write);
}

void	ft_init_machine(t_machine *machine)
{
	M_HEADER = 1;
	M_NAME = 0;
	M_FIRST_NULL = 0;
	M_SIZE = 0;
	M_COMMENT = 0;
	M_SECOND_NULL = 0;
	M_CHAMP_CODE = 0;
	M_START_ROW = 0;
	M_TYPE_BITE = 0;
	M_TYPE_SET = 0;
	M_ARG1 = 0;
	M_ARG2 = 0;
	M_ARG3 = 0;
	M_ARG1_SIZE = 0;
	M_ARG2_SIZE = 0;
	M_ARG3_SIZE = 0;
}
