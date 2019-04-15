/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ_name_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:45:56 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/15 14:43:04 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_current_func_divis(t_asm_data *asm_data, char *line, int i, int j)
{
	if (MACHINE_WAIT_NAME)
	{
		if (j > PROG_NAME_LENGTH)
			ft_error_add(asm_data, ft_strdup("Name too long\n"), i, 2);
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
			ft_error_add(asm_data, ft_strdup("Comment too long\n"), i, 2);
		else
		{
			ft_strncpy(CHAMP_COMMENT, &line[1], j - 1);
			ft_printf("CHAMP COMMENT = %s\n", CHAMP_COMMENT);
		}
		MACHINE_WAIT_COMMENT = 0;
		MACHINE_NAME_COMMENT += 2;
	}
}

int		ft_get_name_or_comment(t_asm_data *asm_data, char *line, int i)
{
	int		j;
	int		temp;

	j = 0;
	if (line[j++] == '"')
	{
		temp = j - 1;
		while (line[j] && line[j] != '"')
			j++;
		if (!line[j])
		{
			ft_error_add(asm_data, ft_strjoin_orig("No close quotes found at\
			 ", &line[temp]), temp, 2);
			return (j + ft_strlen(&line[temp]));
		}
		ft_current_func_divis(asm_data, line, i, j);
	}
	else
	{
		ft_printf("error at %s\n", &line[j - 1]);
		ft_error_add(asm_data, ft_strjoin_orig("An error accured at \
		 ", &line[temp]), temp, 2);
		j = ft_strlen(line) - 1;
	}
	return (j);
}

int		ft_get_name_or_comment_flag(t_asm_data *asm_data, char *line, int i)
{
	if (MACHINE_WAIT_COMMENT || MACHINE_WAIT_NAME)
		return (i + ft_get_name_or_comment(asm_data, line, i));
	if (line[i] == NAME_CMD_STRING[0] && !ft_strncmp(line, NAME_CMD_STRING,\
	ft_strlen(NAME_CMD_STRING)))
	{
		(MACHINE_WAIT_NAME || MACHINE_WAIT_COMMENT) ? (ft_error_add(asm_data,\
		ft_strdup("Name/comment flag alredy was given"), i, 2)) : 0;
		(MACHINE_NAME_COMMENT & 1) ? ft_error_add(asm_data,
		ft_strdup("Name already set"), i, 2) : (MACHINE_WAIT_NAME = 1);
		return (i + ft_strlen(NAME_CMD_STRING) - 1);
	}
	if (line[i] == COMMENT_CMD_STRING[0] && !ft_strncmp(line,\
	COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		(MACHINE_WAIT_NAME || MACHINE_WAIT_COMMENT) ? (ft_error_add(asm_data,\
		ft_strdup("Name/comment flag alredy was given"), i, 2)) : 0;
		(MACHINE_NAME_COMMENT & 1) ? ft_error_add(asm_data,\
		ft_strdup("Comment already set"), i, 2) : (MACHINE_WAIT_NAME = 1);
		return (i + ft_strlen(COMMENT_CMD_STRING) - 1);
	}
	ft_error_add(asm_data, ft_strjoin_orig("Error Unknown type of command \
name/comment: ", &line[0]), i, 2);
	return (i + ft_strlen(&line[0]) - 1);
}

char	*ft_lexer_champ_data(t_asm_data *asm_data, char *line)
{
	int		i;
	int		line_len;
	t_token	*token;

	if (ft_strlen(line) == 0)
		return (line);
	i = 0;
	line_len = ft_strlen(line);
	ft_putendl(line);
	while (i < line_len)
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
