/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:05:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/18 20:37:32 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// ! задание на сегодня - провести синтаксический разбор кода
// ! проверить на то что аргументов не меньше чем должно быть
// ! провести компиляцию
// ! заняться очисткой памяти
// ! Расставить ошибки по типам

void	ft_check_main_params_exists(t_asm_data *asm_data)
{
	if (!(MACHINE_NAME_COMMENT & 1))
		ft_error_add(asm_data, ft_strdup("No Champ's name founded "), 0, 3);
	if (!(MACHINE_NAME_COMMENT & 2))
		ft_error_add(asm_data, ft_strdup("No Champ's comment founded "), 0, 3);
}

void	ft_check_last_row(t_asm_data *asm_data, int fd, int i)
{
	char		*str;
	t_list		*chain;
	t_token		*token;

	str = ft_strnew(31);
	lseek(fd, (off_t)(asm_data->count_symbols - 10), 0);
	read(fd, str, 30);
	while (str[i] == 0 || str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '\n')
	{
		chain = ft_lstnew(NULL, sizeof(t_token));
		token = ft_token_init();
		asm_data->token_size += 1;
		chain->content = token;
		if (asm_data->tokens)
			ft_lstadd_last(asm_data->tokens, chain);
		else
			asm_data->tokens = chain;
		token->row = ASM_NUM_ROW;
		token->str = ft_strdup("\n");
		token->type = Newline;
	}
	else
		ft_error_add(asm_data, ft_strdup("No newline at the end of the file "), 0, 2);
	free (str);
}

void	ft_solve_sequence(t_asm_data *asm_data, int fd)
{
	//todo проверить строку после завершения разработки
	asm_data->count_symbols += ASM_NUM_ROW - 10;
	ft_check_last_row(asm_data, fd, 20);
	ft_check_syntax(asm_data);
	ft_check_main_params_exists(asm_data);
	ft_print_errors(asm_data);
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
	ft_solve_sequence(asm_data, fd);
	(ASM_NUM_ROW > 0) ? free(line) : 0;
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
	ft_putstr("==================================\n");
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
