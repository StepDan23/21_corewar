/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:05:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/12 20:41:12 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//	TODO: подумать как фиксировать последнюю строку!!
//	TODO: Проверить как обрабатывает оригинальный асссемблер случай с .name"name",\
	также глянуть какая ошибка при обработке коммента или имени в центре исходика

// проблема - а что если на другой строке продолжение комментария
// проблема - а что если имя внутри скобок
// проблема - как обрабатывать ошибки
// что такое ошибки в именах - текст перед именем/комментом
//.name "dsjkfdjsf"dg, .name "djfh"dsf", .name 'dhu"gds"fdsf'
//.name
//
//
//"ab.name"
//
// какую-нибудь парашу в начале подам
// комментарий в имени/комментарии
//
//.name #.name "name"
// несколько .name 
// #hjdsfbbdfs
// .name

void	ft_search_camp_name_or_comment_cmd(t_asm *asm_data, char *line, int len)
{
	int		i;

	i = 0;
	NAME_COLUMN = ft_d_strstr(line, NAME_CMD_STRING, COMMENT_CHAR);
	if (NAME_COLUMN == -1)
		COMMENT_COLUM = ft_d_strstr(line, COMMENT_CMD_STRING, COMMENT_CHAR);

	while (line[i])
	{


		// сейчас добавляю проверку на корректный текст в нулевой строке, и добавление ошибки
		ft_printf("%d %d %d\n", STR_DATA_NUM, NAME_COLUMN, COMMENT_COLUM);

		if (!STR_DATA_NUM && (NAME_COLUMN && COMMENT_COLUM))
		{
			ft_error_add(asm_data, line, i, 1);
			break ;
		}


		// * обработка комментария

		i++;
	}
	STR_DATA_NUM++;
}

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
	if (CHAMP_DATA->flag < 3)
	{
		// * пока не считал имя и коммент, или не появился знак ':' флаг будет меньше трёх

		ft_putendl(line);
		if (line[0] == COMMENT_CHAR)
			return ;
		ft_search_camp_name_or_comment_cmd(asm_data, line, len);
		if (STATUS_FLAG == 0)
			STATUS_FLAG = 1;
		else
			STATUS_FLAG = 0;
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
		STR_NUM++;
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
