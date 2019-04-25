/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizasm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:50 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:26:55 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	g_comms[REG_NUMBER][6] = {
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};

int		g_count_of_args[REG_NUMBER] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3,\
	3, 1, 2, 3, 1, 1};

int				g_args_codes[REG_NUMBER] = {
	0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1
};

int				g_t_dir_coefs[REG_NUMBER] = {
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1
};

int		ft_size_of_arg(t_machine *machine, int arg_type, int command)
{
	int		size;

	size = 0;
	if (arg_type == 0 || arg_type > 3)
		return (0);
	else if (arg_type == 1)
		return (1);
	else if (arg_type == 2)
		return (DIR_SIZE / g_t_dir_coefs[command]);
	else
		return (2);
}

void	ft_solve_code(t_machine *machine, int bite, int fd_write)
{
	static int	command_num = 0;

	if (M_START_ROW)
	{
		command_num = bite - 1;
		ft_putstr_fd(g_comms[command_num], fd_write);
		M_TYPE_BITE = g_args_codes[command_num];
		M_START_ROW = 0;
		M_TYPE_SET = 1;
		return ;
	}
	ft_solve_arg_types(machine, bite, fd_write, command_num);
}

void	ft_read_cor_file(int fd_read, int fd_write, int value)
{
	char		*line;
	int			str_num;
	int			k;
	t_machine	machine;

	ft_init_machine(&machine);
	str_num = 0;
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
			k++;
			ft_solve_header(&machine, value, fd_write);
		}
		free(line);
		str_num++;
	}
	(str_num > 0) ? free(line) : 0;
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
	str = ft_strjoin(str, ft_strdup(".txt"));
	fd_write = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_write < 3)
		exit(ft_printf("cant't create file %s.s\n", str));
	ft_read_cor_file(fd_read, fd_write, 0);
	ft_printf("Data write at %s\n", str);
	free(str);
}

int		main(int argc, char *argv[])
{
	int		fd;

	if (argc < 2)
	{
		ft_printf("DizAsm: FATAL ERROR: no input files\n");
		return (0);
	}
	if (ft_get_type_of_file(argv[1], "cor"))
	{
		ft_printf("Error: File {%2s} is wrong type, send .cor file\n", argv[1]);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 3)
	{
		ft_printf("Error: File {%2s} not found\n", argv[1]);
		return (0);
	}
	ft_open_s_file(fd, argv[1]);
	close(fd);
	return (0);
}
