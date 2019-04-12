/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:05:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/12 11:47:33 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//	TODO подумать как фиксировать последнюю строку!!
//	TODO: Проверить как обрабатывает оригинальный асссемблер случай с .name"name",\
	также глянуть какая ошибка при обработке коммента или имени в центре исходика


void	ft_lexer_champ_data(t_asm *asm_data, char *line)
{
	t_rbnode	*node;
	char		*temp_line;
	int			len;
	int			i;

	if ((len = ft_strlen(line)) == 0)
	{
		free(line);
		return ;
	}
	i = 0;
	if (CHAMP_DATA->flag < 3 && (line[0] == NAME_CMD_STRING[0] ||\
	line[0] == COMMENT_CMD_STRING[0]) || (STATUS_FLAG > 0 && STATUS_FLAG < 3))
	{
		ft_putendl(line);
		if (asm_data->status_flag == 0)
			asm_data->status_flag = 1;
		else
			asm_data->status_flag = 0;


		//.name "dsjkfdjsf"dg, .name "djfh"dsf", .name 'dhu"gds"fdsf'
		//.name
		//
		//
		//"ab.name"
		//
		//

	}

}

void	ft_read_file(int fd, char *file_name)
{
	t_asm		*asm_data;
	char		*line;
	int			i;

	i = 0;
	asm_data = ft_asm_init();
	while (get_next_line(fd, &line) > 0)
	{
		ft_lexer_champ_data(asm_data, ft_strtrim(line));
		free(line);
		i++;
	}
	ft_putstr("===========================\n");
	//(i > 0) ? free(line) : 0;
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
