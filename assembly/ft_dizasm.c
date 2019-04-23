/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizasm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:50 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/23 23:27:28 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_init_machine(t_machine *machine)
{
	M_HEADER = 1;
	M_NAME = 0;
	M_FIRST_NULL = 0;
	M_SIZE = 0;
	M_COMMENT = 0;
	M_SECOND_NULL = 0;
	M_CHAMP_CODE = 0;
	M_TEMP = 0;
	M_COUNT = 0;
}

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

void	ft_solve_code(t_machine *machine, int value, int fd_write)
{

}

void	ft_solve_second_null(t_machine *machine, int value, int fd_write)
{
	static int	i = 0;

	if (M_SECOND_NULL)
	{
		i++;
		if (i == 8)
		{
			M_SECOND_NULL = 0;
			M_CHAMP_CODE = 1;
		}
		return ;
	}
	ft_solve_code(machine, value, fd_write);
}

void	ft_solve_comment(t_machine *machine, int value, int fd_write)
{
	static int	i = 0;
	static int	size_of_comment = 0;
	static int	res = 0;

	if (M_COMMENT)
	{
		ft_dizasm_comment(fd_write);
		res += value * ((size_of_comment == 0) ? 16 : 1);
		size_of_comment++;
		if (size_of_comment == 2)
		{
			ft_putchar_fd(res, fd_write);
			res = 0;
			size_of_comment = 0;
		}
		i++;
		if (i == COMMENT_LENGTH)
		{
			M_COMMENT = 0;
			M_SECOND_NULL = 1;
			ft_putstr_fd("\"\n", fd_write);
		}
		return ;
	}
	ft_solve_second_null(machine, value, fd_write);
}

void	ft_solve_size(t_machine *machine, int value, int fd_write)
{
	static int	i = 0;

	if (M_SIZE)
	{
		i++;
		if (i == 8)
		{
			M_SIZE = 0;
			M_COMMENT = 1;
		}
		return ;
	}
	ft_solve_comment(machine, value, fd_write);
}

void	ft_solve_first_null(t_machine *machine, int value, int fd_write)
{
	static int	i = 0;

	if (M_FIRST_NULL)
	{
		i++;
		if (i == 8)
		{
			M_FIRST_NULL = 0;
			M_SIZE = 1;
		}
		return ;
	}
	ft_solve_size(machine, value, fd_write);
}

void	ft_solve_name(t_machine *machine, int value, int fd_write)
{
	static int	i = 0;
	static int	size_of_name = 0;
	static int	res = 0;

	if (M_NAME)
	{
		ft_dizasm_name(fd_write);
		res += value * ((size_of_name == 0) ? 16 : 1);
		size_of_name++;
		if (size_of_name == 2)
		{
			ft_putchar_fd(res, fd_write);
			res = 0;
			size_of_name = 0;
		}
		i++;
		if (i == PROG_NAME_LENGTH)
		{
			M_NAME = 0;
			M_FIRST_NULL = 1;
			ft_putstr_fd("\"\n", fd_write);
		}
		return ;
	}
	ft_solve_first_null(machine, value, fd_write);
}

void	ft_solve_strings(t_machine *machine, int value, int fd_write)
{
	static int		i = 0;

	if (value == ' ')
		return ;
	if (M_HEADER)
	{
		i++;
		if (i == 8)
		{
			M_HEADER = 0;
			M_NAME = 1;
		}
		return ;
	}
	ft_solve_name(machine, value, fd_write);
}

void	ft_read_cor_file(int fd_read, int fd_write, int value)
{
	char		*line;
	int			j;
	int			k;
	t_machine	machine;

	ft_init_machine(&machine);
	j = 0;
	while (get_next_line(fd_read, &line) > 0)
	{
		k = 0;
		while (line[k])
		{
			if (line[k] >= 'a' && line[k] <= 'f')
				value = line[k] - 'a' + 10;
			else if (line[k] >= '0' && line[k] <= '9')
				value = line[k] - '0';
			else if (line[k] == ' ')
				value = ' ';
			ft_solve_strings(&machine, value, fd_write);
		}
		free(line);
		j++;
	}
	(j > 0) ? free(line) : 0;
}

void	ft_open_s_file(int fd_read, char *file_name)
{
	int		fd_write;
	char	*str;
	int		j;

	j = 0;
	while (file_name[j] && file_name[j] != '.')
		j++;
	str = ft_strsub(file_name, 0, j);
	fd_write = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_write < 3)
		exit(ft_printf("cant't create file %s.s\n", str));
	free(str);
	ft_read_cor_file(fd_read, fd_write, 0);
}

int		main(int argc, char *argv[])
{
	int		fd;

	if (argc < 2)
	{
		ft_printf("DizAsm: FATAL ERROR: no input files\n");
		return (0);
	}
	if (ft_get_type_of_file(argv[2], ".cor"))
	{
		ft_printf("Error: File {%2s} is wrong type, send .cor file\n", argv[2]);
		return (0);
	}
	fd = open(argv[2], O_RDONLY);
	if (fd < 3)
	{
		ft_printf("Error: File {%2s} not found\n", argv[2]);
		return (0);
	}
	ft_open_s_file(fd, argv[2]);
	close(fd);
	return (0);
}
