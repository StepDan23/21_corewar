/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:46:59 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/15 21:15:15 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
	в этой секции нужно проверять:
	имя команды,
	ее атрибуты,
	метки,

*/

int	ft_get_word_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && \
	line[i] != COMMENT_CHAR && line[i] != DIRECT_CHAR && line[i] != 'r' && \
	line[i] != LABEL_CHAR && line[i] != SEPARATOR_CHAR)
		i++;
	ft_printf("WORD len = %d\n", i);
	return (i);
}

char	*ft_lexer_champ_code(t_asm_data *asm_data, char *line)
{
	int		i;

	i = 0;
	ft_putendl(line);
	while (line[i])
	{
		i = ft_get_word_len(&line[i]);
	}
	return (line);
}
