/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:46:59 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/15 23:50:13 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
	в этой секции нужно проверять:
	имя команды,
	ее атрибуты,
	метки,
	! Проверять тип элемента последовательно - сначала на пробелб потом на метку, потом на r1,
	! потом %, потом число потом, на комманду. Сделать паровоз из функций
*/

int	ft_get_word_len(char *line)
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

void	ft_fill_token(t_asm_data *asm_data, char *line)
{
	ft_printf("%s\n", line);
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
