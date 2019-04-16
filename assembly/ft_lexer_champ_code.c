/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:46:59 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/16 19:40:47 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
** в этой секции нужно проверять:
** имя команды,
** ее атрибуты,
** метки,
** ! Проверять тип элемента последовательно - %, потом комманду.
*/

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
	if (i > 0)
	{
		ft_printf("\n WORD len = %i ", i);
		return (i);
	}
	if (line[i] == ' ' || line[i] == '\t')
		return (1);
	return (0);
}

int		ft_string_contain_only_num(char	*str)
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

char	*ft_lexer_champ_code(t_asm_data *asm_data, char *line)
{
	int		i;
	int		word_len;
	t_token	*token;
	t_list	*chain;

	i = 0;
	ft_putendl(line);
	if (!MACHINE_NEW_LINE)
		ft_add_new_str_token(asm_data);
	while (line[i])
	{
		word_len = ft_get_word_len(&line[i]);
		chain = ft_lstnew(NULL, sizeof(t_token));
		token = ft_token_init();
		chain->content = token;
		ft_lstadd_last((asm_data->tokens), chain);
		token->row = ASM_NUM_ROW;
		token->col = i;
		ft_fill_token(asm_data, ft_strsub(line, i, word_len));
		i += word_len;
	}
	return (line);
}
