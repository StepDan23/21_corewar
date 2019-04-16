/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:05:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/16 14:20:15 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//	? подумать как фиксировать последнюю строку!! - сравнивать токен последней строки с общим числом строк
//	TODO: Проверить как обрабатывает оригинальный асссемблер случай с .name"name",\
	также глянуть какая ошибка при обработке коммента или имени в центре исходика
// !переход на новую строку в имени и комменте
// !ошибка если нет имени или коммента и началось чтение второй части кода

void	ft_read_file(int fd, char *file_name)
{
	t_asm_data	*asm_data;
	char		*trim_line;
	char		*line;
	int			i;

	i = 0;
	asm_data = ft_asm_data_init();
	while (get_next_line(fd, &line) > 0)
	{
		MACHINE_NEW_LINE = 0;
		trim_line = ft_strtrim(line);
		(MACHINE_NAME_COMMENT >= 3) ? free(ft_lexer_champ_code(asm_data, trim_line)) : 0;
		(MACHINE_NAME_COMMENT < 3) ? free(ft_lexer_champ_data(asm_data, trim_line)) : 0;
		free(line);
		ASM_NUM_ROW++;


		i++;
	}
	ft_putstr("===========================\n");
	ft_print_errors(asm_data);
	(i > 0) ? free(line) : 0;
	free(asm_data);
}

void	ft_start_compile_sequence(char *file_name)
{
	int			fd;

	if (ft_get_type_of_file(file_name, "s"))
	{
		ft_printf("Error: File {%2s} is wrong type, send .s file\n", file_name);
		return;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 3)
	{
		ft_printf("Error: File {%2s} not found\n", file_name);
		return ;
	}
	ft_read_file(fd, file_name);
	close(fd);
}


int		main(int argc, char *argv[])
{
	char	**files_to_compile;
	int		i;

	if (argc < 2)
	{
		ft_printf("asm: FATAL ERROR: no input files\ncompilation terminated\n");
		return (0);
	}
	i = 0;
	files_to_compile = (argc == 2) ? ft_strsplit(argv[1], ' ') : &argv[1];
	if (argc == 2)
		while(files_to_compile[i])
			ft_start_compile_sequence(files_to_compile[i++]);
	else
		while(i < argc - 1)
			ft_start_compile_sequence(files_to_compile[i++]);
	if (argc == 2)
	{
		while (i > 0)
			free(files_to_compile[i-- - 1]);
		free(files_to_compile);
	}
	return (0);
}
