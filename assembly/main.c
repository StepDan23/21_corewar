/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:05:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/15 01:05:18 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//	? подумать как фиксировать последнюю строку!! - сравнивать токен последней строки с общим числом строк
//	TODO: Проверить как обрабатывает оригинальный асссемблер случай с .name"name",\
	также глянуть какая ошибка при обработке коммента или имени в центре исходика

// проблема - а что если на другой строке продолжение комментария
// проблема - а что если имя внутри скобок
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

int	ft_strlen_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '#' &&\
	line[i] != '\'' && line[i] != '\"' && line[i] != '%' && line[i] != 'r')
		i++;
	return (i);
}

int	ft_get_name_or_comment(t_asm_data *asm_data, char *line, int i)
{
	//ft_printf("name or comment name == %s\n", &line[i]);
	int		j;

	j = 0;
	if (line[j++] == '"')
	{
		while (line[j] && line[j] != '"')
			j++;
		if (MACHINE_WAIT_NAME)
		{
			if (j > PROG_NAME_LENGTH)
				ft_printf("Name is too long\n");
			else
			{
				ft_strncpy(CHAMP_NAME, &line[1], j - 1);
				ft_printf("CHAMP NAME = %s\n", CHAMP_NAME);
			}
			MACHINE_WAIT_NAME = 0;
			MACHINE_NAME_COMMENT += 1;
		}
		if (MACHINE_WAIT_COMMENT)
		{
			if (j > COMMENT_LENGTH)
				ft_printf("COMMENT is too long\n");
			else
			{
				ft_strncpy(CHAMP_COMMENT, &line[1], j - 1);
				ft_printf("CHAMP COMMENT = %s\n", CHAMP_COMMENT);
			}
			MACHINE_WAIT_COMMENT = 0;
			MACHINE_NAME_COMMENT += 2;
		}
	}
	else
	{
		ft_printf("error at %s\n", &line[i]);
	}
	return (i + j);
}

int		ft_get_name_or_comment_flag(t_asm_data *asm_data, char *line, int i)
{
	if (MACHINE_WAIT_COMMENT || MACHINE_WAIT_NAME)
		return (ft_get_name_or_comment(asm_data, line, i));
	if (line[i] == NAME_CMD_STRING[0] && !MACHINE_WAIT_COMMENT && !MACHINE_WAIT_NAME)
	{
		if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			MACHINE_WAIT_NAME = 1;
			return (i + ft_strlen(NAME_CMD_STRING) - 1);
		}
	}
	if (line[i] == COMMENT_CMD_STRING[0] && !MACHINE_WAIT_COMMENT && !MACHINE_WAIT_NAME)
	{
		if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			MACHINE_WAIT_COMMENT = 1;
			return (i + ft_strlen(COMMENT_CMD_STRING) - 1);
		}
	}
		//это эррор мэнеджер для имен. Почекать после завершения считывания имени
		ft_printf("error_at %s\n", &line[i]);
		return (i + ft_strlen(&line[i]) - 1);
}

char	*ft_lexer_champ_data(t_asm_data *asm_data, char *line)
{
	int		i;
	t_token	*token;

	if (ft_strlen(line) == 0)
		return (line);
	i = 0;
	ft_putendl(line);
	while (line[i] && MACHINE_NAME_COMMENT < 3)
	{
		while(line[i] && line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == COMMENT_CHAR)
			return (line);
		i = ft_get_name_or_comment_flag(asm_data, &line[i], i);
		i++;
	}
	return (line);
}

void	ft_read_file(int fd, char *file_name)
{
	t_asm_data	*asm_data;
	char		*line;
	int			i;

	i = 0;
	asm_data = ft_asm_data_init();
	while (get_next_line(fd, &line) > 0)
	{

		free(ft_lexer_champ_data(asm_data, ft_strtrim(line)));
		free(line);
		ASM_NUM_ROW++;
		i++;
	}
	ft_putstr("===========================\n");
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
