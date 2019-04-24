/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ_name_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:14:19 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 17:31:52 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_wrong_quotes(t_asm_data *asm_data, char *line, int i, int j)
{
	while (line[++j] && line[j] != '\'')
		;
	if (line[j] == '\'')
		ft_error_add(asm_data, ft_strdup("Wrong quotes "), i, 1);
	else
		ft_error_add(asm_data, ft_strdup("Wrong quotes and no end "), i, 1);
	return (j);
}

int		ft_get_name_or_comment(t_asm_data *asm_data, char *line, int i, int k)
{
	int		j;
	int		temp;

	j = 0;
	if (line[j] == '\'')
		return (ft_wrong_quotes(asm_data, line, i + k, j));
	if (line[j++] == '"')
	{
		temp = j - 1;
		while (line[j] && line[j] != '"')
			j++;
		if (!line[j])
		{
			MACHINE_DOUBLE_QUOTES = 1;
			return (j + ft_strlen(&line[temp]));
		}
		ft_current_func_divis(asm_data, line, i + k, j);
	}
	else
	{
		ft_error_add(asm_data, ft_strdup("Some unidentified error \
oqqured while set name or comment: "), k, 2);
		j = ft_strlen(line) - 1;
	}
	return (j);
}

int		ft_get_name_or_comment_flag(t_asm_data *asm_data, char *line,\
int i, int j)
{
	if (line[0] == NAME_CMD_STRING[0] && !ft_strncmp(line, NAME_CMD_STRING,\
	ft_strlen(NAME_CMD_STRING)))
	{
		(MACHINE_WAIT_COMMENT || MACHINE_WAIT_NAME) ? (ft_error_add(asm_data,\
		ft_strdup("CHAMP's CMD alredy was given"), i + j, 3)) : 0;
		(MACHINE_NAME_COMMENT & 1) ? ft_error_add(asm_data,
		ft_strdup("Name already set"), i + j, 3) : (MACHINE_WAIT_NAME = 1);
		return (i + ft_strlen(NAME_CMD_STRING) - 1);
	}
	if (line[0] == COMMENT_CMD_STRING[0] && !ft_strncmp(line,\
	COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		(MACHINE_WAIT_COMMENT || MACHINE_WAIT_NAME) ? (ft_error_add(asm_data,\
ft_strdup("CHAMP's CMD alredy was given"), i + j, 3)) : 0;
		(MACHINE_NAME_COMMENT & 2) ? ft_error_add(asm_data,\
ft_strdup("Comment was set earlier"), i + j, 3) : (MACHINE_WAIT_COMMENT = 1);
		return (i + ft_strlen(COMMENT_CMD_STRING) - 1);
	}
	if (MACHINE_WAIT_COMMENT || MACHINE_WAIT_NAME)
		return (i + ft_get_name_or_comment(asm_data, line, i, j));
	ft_error_add(asm_data, ft_strjoin_orig("Error Unknown type of command \
name/comment: ", &line[0]), i + j, 2);
	return (i + ft_strlen(&line[0]) - 1);
}

int		ft_add_text_in_quotes(t_asm_data *asm_data, char *line, int i)
{
	while (line[i] && line[i] != '"')
		i++;
	if (MACHINE_WAIT_NAME)
	{
		CHAMP_NAME = ft_strjoin(CHAMP_NAME, ft_strsub(line, 0, i));
		if (line[i] == '"')
		{
			MACHINE_DOUBLE_QUOTES = 0;
			MACHINE_WAIT_NAME = 0;
			MACHINE_NAME_COMMENT += 1;
		}
	}
	if (MACHINE_WAIT_COMMENT)
	{
		CHAMP_COMMENT = ft_strjoin(CHAMP_COMMENT, ft_strsub(line, 0, i));
		if (line[i] == '"')
		{
			MACHINE_DOUBLE_QUOTES = 0;
			MACHINE_WAIT_COMMENT = 0;
			MACHINE_NAME_COMMENT += 2;
		}
	}
	return (i);
}

char	*ft_lexer_champ_data(t_asm_data *asm_data, char *line, int j)
{
	int		i;
	int		line_len;

	if ((line_len = ft_strlen(line)) == 0)
		return (line);
	i = 0;
	while (i < line_len)
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == COMMENT_CHAR || line[i] == ANOTHER_COMMENT_CHAR)
			return (line);
		if (MACHINE_DOUBLE_QUOTES)
			i = ft_add_text_in_quotes(asm_data, line, 0);
		else
			i = ft_get_name_or_comment_flag(asm_data, &line[i], i, j);
		i++;
	}
	return (line);
}
