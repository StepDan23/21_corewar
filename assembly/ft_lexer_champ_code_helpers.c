/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:23:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 21:17:13 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	g_commands[16][6] = {
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};

int		ft_line_is_command(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (i <= 16)
	{
		j = 0;
		while (line[j] == g_commands[i][j] && line[j] && g_commands[i][j])
			j++;
		if (g_commands[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_find_sym(char *line, char sym)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] != sym) && line[i] != COMMENT_CHAR)
		i++;
	if (line[i] && line[i] != COMMENT_CHAR)
		return (i);
	else
		return (0);
}

int		ft_check_label_symbols(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != ':')
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (LABEL_CHARS[j] == line[i])
				break ;
			j++;
		}
		if (!LABEL_CHARS[j])
			return (0);
		i++;
	}
	return (1);
}

int		ft_get_word_len(char *line)
{
	int	i;

	i = 0;
	if (line[0] == LABEL_CHAR)
		i++;
	if (line[0] == DIRECT_CHAR && line[1] == LABEL_CHAR)
		i += 2;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && \
	line[i] != COMMENT_CHAR && line[i] != LABEL_CHAR &&
	line[i] != SEPARATOR_CHAR)
		i++;
	if (line[0] == SEPARATOR_CHAR && i == 0)
		i++;
	if (line[i] == ':' && i != 0)
		i++;
	if (i > 0)
	{
		ft_printf("\n WORD len = %i ", i);
		return (i);
	}
	if (line[i] == ' ' || line[i] == '\t')
		return (1);
	return (0);
}

int		ft_string_contain_only_num(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == 0)
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
