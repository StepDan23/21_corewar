/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:46:59 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/16 00:24:25 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
	в этой секции нужно проверять:
	имя команды,
	ее атрибуты,
	метки,
	! Проверять тип элемента последовательно - сначала на пробел потом на метку, потом на r1,
	! потом %, потом число потом, на комманду. Сделать паровоз из функций
*/

int		ft_find_sym(char *line, char *sym)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != sym && line[i] != COMMENT_CHAR)
		i++;
	if (line[i] && line[i] != COMMENT_CHAR)
		return (i);
	else
		return (-1);
}

int		ft_check_label_sym(char *line)
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
			if (LABEL_CHARS[j] = line[i])
				break ;
			j++;
		}
		if (!LABEL_CHARS[j])
			return (0);
	}
	return (1);
}

int		ft_get_word_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && \
	line[i] != COMMENT_CHAR && line[i] != DIRECT_CHAR && line[i] != 'r' && \
	line[i] != LABEL_CHAR && line[i] != SEPARATOR_CHAR)
		i++;
	if (i > 0)
	{
		//ft_printf("WORD len = %i\n", i);
		return (i);
	}
	if (line[i] == ' ' || line[i] == '\t')
		return (1);
	return (0);
}

void	ft_fill_token2(t_asm_data *asm_data, char *line)
{
	if (line[0] == 'r')
	{
		//если строка число то все ок, если нет то добавляем ошибку
	}
}

void	ft_fill_token(t_asm_data *asm_data, char *line)
{
	ft_printf("%s\n", line);
	TOKEN_DATA->str = line;
	//здесь определение типов токенов
	if (line[0] == ' ' || line[0] == '\t')
	{
		TOKEN_DATA->type = Whitespace;
		return ;
	}
	if (ft_find_sym(line, LABEL_CHAR))
	{
		if (ft_check_label_sym(line))
			TOKEN_DATA->type = Label;
		else
		{
			TOKEN_DATA->type = Unknown;
			ft_error_add(asm_data, ft_strjoin("Wrong symbols in label ", line),\
			 TOKEN_DATA->col, TOKEN_DATA->row);
		}
		return ;
	}
	ft_fill_token2(asm_data, line);
}

char	*ft_lexer_champ_code(t_asm_data *asm_data, char *line)
{
	int		i;
	int		word_len;
	t_token	*token;
	t_list	*chain;

	i = 0;
	ft_putendl(line);
	while (line[i])
	{
		word_len = ft_get_word_len(&line[i]);
		chain = ft_lstnew(NULL, sizeof(t_token));
		token = ft_token_init();
		chain->content = token;
		if (ASM_TOKENS == NULL)
			ASM_TOKENS = chain;
		else
			ft_lstadd_last(&ASM_TOKENS, chain);
		token->row = ASM_NUM_ROW;
		token->col = i;
		ft_fill_token(asm_data, ft_strsub(line, i, word_len));
		i += word_len;
	}
	return (line);
}
