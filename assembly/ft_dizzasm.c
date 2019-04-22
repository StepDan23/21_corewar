/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dizzasm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:50 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 21:49:51 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dizasm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_init_machine(t_machine *machine)
{
	M_HEADER = 0;
	M_NAME = 0;
	M_FIRST_NULL = 0;
	M_SIZE = 0;
	M_COMMENT = 0;
	M_SECOND_NULL = 0;
	M_CHAMP_CODE = 0;
	M_TEMP = 0;
}

void	ft_solve_strings(char *line, int *i, int fd_write)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	ft_putednl(line);
	while (line[j])
	{
		j++;
	}
}

void	ft_read_cor_file(int fd_read, int ft_write)
{
	char		*line;
	int			j;
	int			i;
	t_machine	machine;

	ft_init_machine(&machine);
	j = 0;
	i = 0;
	while (get_next_line(fd_read, &line) > 0)
	{
		ft_solve_strings(line, &i, ft_write);
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
	ft_read_cor_file(fd_read, fd_write);
}

int		main(int argc, char *argv[])
{
	int		fd;

	if (argc < 2)
	{
		ft_printf("asm: FATAL ERROR: no input files\n");
		return (0);
	}
	if (ft_get_type_of_file(argv[2], ".cor"))
	{
		ft_printf("Error: File {%2s} is wrong type, send .cor file\n", argv[2]);
		return ;
	}
	fd = open(argv[2], O_RDONLY);
	if (fd < 3)
	{
		ft_printf("Error: File {%2s} not found\n", argv[2]);
		return ;
	}
	ft_open_s_file(fd, argv[2]);
	close(fd);
	return (0);
}
