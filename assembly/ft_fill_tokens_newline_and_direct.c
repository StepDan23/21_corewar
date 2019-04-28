/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tokens_newline_and_direct.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:42:54 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 19:29:41 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_new_str_token(t_asm_data *asm_data)
{
	t_token	*token;
	t_list	*chain;

	chain = ft_lstnew(NULL, 0);
	token = ft_token_init();
	chain->content = token;
	if (ASM_TOKENS == NULL)
		ASM_TOKENS = chain;
	else
		ft_lstadd_last(ASM_TOKENS, chain);
	token->row = ASM_NUM_ROW - 1;
	token->col = 0;
	token->str = ft_strdup("\n");
	token->type = Newline;
	asm_data->token_size += 1;
	MACHINE_NEW_LINE = 1;
}

void	ft_fill_token_direct_labels(t_asm_data *asm_data, char *line,\
t_token *token)
{
	if (ft_check_label_symbols(line))
		token->type = Direct_label;
	else
	{
		token->type = Unknown;
		ft_error_add(asm_data, ft_strjoin_orig("Wrong symbols in label ",\
		token->str), token->col, 1);
	}
}

void	ft_fill_token_direct_digits(t_asm_data *asm_data, char *line,\
t_token *token)
{
	long long	temp;

	token->type = Unknown;
	if (line[0] == '+')
	{
		ft_error_add(asm_data, ft_strjoin_orig("Direct Num contains plus ",\
		token->str), token->col, 1);
		return ;
	}
	token->type = Direct_number;
}

void	ft_clear_label_temp(t_asm_data *asm_data)
{
	t_list	*current;
	t_list	*last;

	current = ASM_LABEL;
	while (current)
	{
		last = current;
		current = current->next;
		free(last);
	}
}
