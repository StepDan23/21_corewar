/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:31:28 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 21:05:53 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_clear_tokens(t_asm_data *asm_data)
{
	t_list	*current;
	t_list	*last;
	t_token	*token;

	current = ASM_TOKENS;
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
	ft_clear_rows(asm_data);
	ft_clear_labels(asm_data);
}
