/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:09:07 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/18 22:34:31 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	g_comms[REG_NUMBER][6] = {
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

t_table_ops	*g_ops = NULL;

int		ft_is_arg_valid(t_types type, int cur_arg, int com_num, t_token *token)
{
	int		value;
	int		token_value;

	if (cur_arg == 1)
		value = g_ops->arg1_type[com_num];
	else if (cur_arg == 2)
		value = g_ops->arg2_type[com_num];
	else if (cur_arg == 3)
		value = g_ops->arg3_type[com_num];
	token_value = ft_token_type_value(token->type);
	if (value & token_value)
		return (1);
	else
		return (0);
}

void	ft_row_args_check(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if (ROW_WAIT_SEP)
	{
		ft_error_token(asm_data, ft_strdup("Two args in row "),\
		TKN_ROW, TKN_COL, 1);
		ROW_CNT_ARG++;
		return ;
	}
	if (ROW_CNT_ARG - 1 >= ROW_CNT_MAX)
	{
		ft_error_token(asm_data, ft_strdup("Extra param for command "),\
		TKN_ROW, TKN_COL, 1);
		return ;
	}
	if (!ft_is_arg_valid(TKN_TYPE, ROW_CNT_ARG, ROW_COM_NUM, token))
	{
		ft_error_token(asm_data, ft_strdup("Wrong type of arg "),\
		TKN_ROW, TKN_COL, 1);
		ROW_CNT_ARG++;
		return ;
	}
	ROW_ARG_CODE += ft_token_type_value(TKN_TYPE);
	ROW_ARGS_TEXT[ROW_CNT_ARG - 1] = ft_strdup(TKN_STR);
	ROW_CNT_ARG++;
	ROW_WAIT_SEP = 1;
}

void	ft_add_new_command_row(t_asm_data *asm_data, t_token *token,\
t_syntax_row *row)
{
	t_list			*synt_row;

	row = ft_syn_row_init();
	synt_row = ft_lstnew(NULL, (sizeof(t_syntax_row)));
	synt_row->content = row;
	ROW_NUM = (!ROW_NUM) ? token->row : ROW_NUM;
	ROW_COM_NUM = ft_line_is_command(token->str);
	ROW_COM_NUM = (ROW_COM_NUM == -1) ? 0 : ROW_COM_NUM;
	ROW_CNT_MAX = g_ops->count_of_args[ROW_COM_NUM];
	ROW_ARGS_TEXT = ft_memalloc(8 * ROW_CNT_MAX);
	ASM_SYNTAX_ROW_COUNT++;
	if (asm_data->syntax_row)
		ft_lstadd_last(asm_data->syntax_row, synt_row);
	else
		asm_data->syntax_row = synt_row;
}

void	ft_start_fill_rows(t_asm_data *asm_data, t_list *token_chain,\
t_list *labels, t_token *token)
{
	while (token_chain)
	{
		token = (t_token *)(token_chain->content);
		if (token->type == Label)
		{
			token_chain = token_chain->next;
			continue ;
		}
		else
			ft_fill_strings(asm_data, token, labels);
		token_chain = token_chain->next;
	}
}

// завтра день лэйблов

void	ft_check_syntax(t_asm_data *asm_data)
{
	t_token		*token;
	t_list		*labels;
	t_list		*token_chain;

	g_ops = ft_table_operations_init();
	labels = ft_collect_labels(asm_data, 1);
	token_chain = (asm_data->tokens);
	token = (t_token *)(token_chain->content);
	while (token_chain && (token->type == Newline || token->type == Whitespace))
	{
		token_chain = token_chain->next;
		token = (t_token *)(token_chain->content);
	}
	ft_start_fill_rows(asm_data, token_chain, labels, token);
	ft_check_syntax_rows(asm_data, asm_data->syntax_row);
}
