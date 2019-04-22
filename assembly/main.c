/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:16:48 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 17:03:46 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// ! а что если несколько функций в ряд? не приведет ли это к тому что  в файле будет несколько кодов?
// ! заняться очисткой памяти
// ! Расставить ошибки по типам

void	ft_clear_tokens(t_asm_data *asm_data)
{
	t_list	*current;
	t_list	*last;
	t_token	*token;
	
	current = asm_data->tokens;
	while (current)
	{
		token = (t_token *)(current->content);
		free(token->str);
		last = current;
		current = current->next;
		free(last->content);
		free(last);
	}
	ASM_TOKENS = NULL;
}

void	ft_clear_errors(t_asm_data *asm_data)
{
	t_list		*current;
	t_list		*last;
	t_errors	*error;
	int			i;

	i = 0;
	current = ERRORS;
	while (i < ERROR_SIZE - 1)
	{
		error = (t_errors *)(current->content);
		free(error->error_str);
		last = current;
		current = current->next;
		free(last->content);
		free(last);
		i++;
	}
	ERRORS = NULL;
}

void	ft_clear_rows(t_asm_data *asm_data)
{
	t_list			*current;
	t_list			*last;
	t_syntax_row	*row;
	int				i;

	current = ASM_SYNTAX_ROW;
	while (current)
	{
		row = (t_syntax_row *)(current->content);
		i = 0;
		while (i < ROW_CNT_MAX)
			free(ROW_ARGS_TEXT[i++]);
		free(ROW_ARGS_TEXT);
		free(ROW_ARGS_SIZES);
		free(ROW_ARG_TYPES);
		last = current;
		current = current->next;
		free(last->content);
		free(last);
	}
	ASM_SYNTAX_ROW = NULL;
}

void	ft_clear_labels(t_asm_data *asm_data)
{
	t_list				*current;
	t_list				*last;
	t_label_compile		*label;

	current = ASM_LABEL;
	while (current)
	{
		label = (t_label_compile *)(current->content);
		free(label->label_text);
		last = current;
		current = current->next;
		free(last->content);
		free(last);
	}
	ASM_LABEL = NULL;
}

void	ft_clear_memory(t_asm_data *asm_data)
{
	free(ASM_CHAMP_DATA->champ_name);
	free(ASM_CHAMP_DATA->champ_comment);
	free(ASM_CHAMP_DATA);
	ft_clear_tokens(asm_data);
	free(ASM_STATE_MACHINE);
	ft_clear_errors(asm_data);
	ft_clear_rows(asm_data);
	ft_clear_labels(asm_data);
}

void	ft_solve_sequence(t_asm_data *asm_data, int fd, char *filename)
{
	//todo проверить строку после завершения разработки
	asm_data->count_symbols += ASM_NUM_ROW - 10;
	ft_check_last_row(asm_data, fd, 20);
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
	ft_putstr("==================================\n");
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
