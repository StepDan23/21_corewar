/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:12:32 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 17:31:45 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*ft_lexer_champ_code(t_asm_data *asm_data, char *line, int j)
{
	int		i;
	int		word_len;
	t_token	*token;
	t_list	*chain;

	i = 0;
	if (!MACHINE_NEW_LINE)
		ft_add_new_str_token(asm_data);
	while (line[i])
	{
		word_len = ft_get_word_len(&line[i]);
		if (line[i] == COMMENT_CHAR || line[i] == ANOTHER_COMMENT_CHAR)
			return (line);
		chain = ft_lstnew(NULL, 0);
		token = ft_token_init();
		chain->content = token;
		ASM_TOKEN_SIZE += 1;
		ft_lstadd_last(ASM_TOKENS, chain);
		TKN_ROW = ASM_NUM_ROW;
		TKN_COL = i + j;
		ft_fill_token(asm_data, ft_strsub(line, i, word_len), token);
		i += word_len;
	}
	return (line);
}
