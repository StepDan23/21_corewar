/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:16:48 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 17:18:11 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_solve_sequence(t_asm_data *asm_data, int fd, char *filename)
{
	asm_data->count_symbols += ASM_NUM_ROW - 10;
	ft_check_last_row(asm_data, fd, 0);
	ft_check_syntax(asm_data);
	ft_check_main_params_exists(asm_data);
	if (asm_data->error_list_size > 0)
		ft_print_errors(asm_data);
	else
		ft_convert_to_binary(asm_data, filename);
	ft_clear_memory(asm_data);
}

void	ft_read_file(int fd, char *file_name)
{
	t_asm_data	*asm_data;
	char		*line;
	int			j;

	j = 0;
	asm_data = ft_asm_data_init();
	while (get_next_line(fd, &line) > 0)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j += (line[j] == ' ') ? 1 : 4;
		MACHINE_NEW_LINE = 0;
		(MACHINE_NAME_COMMENT >= 3) ? free(ft_lexer_champ_code(asm_data,\
		ft_strtrim(line), j)) : 0;
		(MACHINE_NAME_COMMENT < 3) ? free(ft_lexer_champ_data(asm_data,\
		ft_strtrim(line), j)) : 0;
		asm_data->count_symbols += ft_strlen(line);
		free(line);
		ASM_NUM_ROW++;
	}
	ft_solve_sequence(asm_data, fd, file_name);
	(ASM_NUM_ROW > 0) ? free(line) : 0;
	free(asm_data);
}

void	ft_start_compile_sequence(char *file_name)
{
	int			fd;

	if (ft_get_type_of_file(file_name, "s"))
	{
		ft_printf("Error: File {%2s} is wrong type, send .s file\n", file_name);
		return ;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 3)
	{
		ft_printf("Error: File {%2s} not found\n", file_name);
		return ;
	}
	ft_read_file(fd, file_name);
	ft_putendl("=============================================================");
	close(fd);
}

int		main(int argc, char *argv[])
{
	char	**files_to_compile;
	int		i;

	if (argc < 2)
	{
		ft_printf("asm: FATAL ERROR: no input files\n");
		return (0);
	}
	i = 0;
	files_to_compile = (argc == 2) ? ft_strsplit(argv[1], ' ') : &argv[1];
	if (argc == 2)
		while (files_to_compile[i])
			ft_start_compile_sequence(files_to_compile[i++]);
	else
		while (files_to_compile[i])
			ft_start_compile_sequence(files_to_compile[i++]);
	if (argc == 2)
	{
		while (i > 0)
			free(files_to_compile[i-- - 1]);
		free(files_to_compile);
	}
	return (0);
}
