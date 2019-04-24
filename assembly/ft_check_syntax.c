/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:09:07 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 17:16:29 by lshanaha         ###   ########.fr       */
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

size_t		g_label_num = 0;

int		ft_is_arg_valid(int cur_arg, int com_num, t_token *token)
{
	int		value;
	int		token_value;

	value = 0;
	if (cur_arg == 1)
		value = g_ops->arg1_type[com_num];
	else if (cur_arg == 2)
		value = g_ops->arg2_type[com_num];
	else if (cur_arg == 3)
		value = g_ops->arg3_type[com_num];
	token_value = ft_type_value(token->type);
	if (value & token_value)
		return (1);
	else
		return (0);
}

void	ft_row_args_check(t_asm_data *asm_data, t_token *token,\
t_syntax_row *row)
{
	if (ROW_WAIT_SEP)
	{
		ft_error_token(asm_data, ft_strdup("Two args in row "), token, 2);
		ROW_CNT_ARG++;
		return ;
	}
	if (ROW_CNT_ARG - 1 >= ROW_CNT_MAX)
	{
		ft_error_token(asm_data, ft_strdup("Extra param for command "),\
		token, 2);
		return ;
	}
	if (!ft_is_arg_valid(ROW_CNT_ARG, ROW_COM_NUM, token))
	{
		ft_error_token(asm_data, ft_strdup("Wrong type of arg "),\
		token, 3);
		ROW_CNT_ARG++;
		return ;
	}
	ROW_ARG_CODE += ft_cnt_arg(ft_type_value(TKN_TYPE), ROW_CNT_ARG,\
	TABLE_FLAG[ROW_COM_NUM]);
	ROW_ARGS_TEXT[ROW_CNT_ARG - 1] = ft_strdup(TKN_STR);
	ROW_ARG_TYPES[ROW_CNT_ARG - 1] = TKN_TYPE;
	ft_row_wrapper(row);
}

void	ft_add_new_command_row(t_asm_data *asm_data, t_token *token)
{
	t_list			*synt_row;
	t_syntax_row	*row;

	row = ft_syn_row_init();
	synt_row = ft_lstnew(NULL, (sizeof(t_syntax_row)));
	free(synt_row->content);
	synt_row->content = row;
	ROW_NUM = (!ROW_NUM) ? token->row : ROW_NUM;
	ROW_COM_NUM = ft_line_is_command(token->str);
	ROW_COM_NUM = (ROW_COM_NUM == -1) ? 0 : ROW_COM_NUM;
	ROW_CNT_MAX = g_ops->count_of_args[ROW_COM_NUM];
	ROW_ARGS_TEXT = ft_memalloc(8 * ROW_CNT_MAX);
	ROW_ARG_TYPES = ft_memalloc(sizeof(t_types) * ROW_CNT_MAX);
	ROW_ARGS_SIZES = ft_memalloc(4 * ROW_CNT_MAX);
	ROW_T_DIR_COEF = g_ops->t_dir_coefs[ROW_COM_NUM];
	ASM_SYNTAX_ROW_COUNT++;
	if (asm_data->syntax_row)
		ft_lstadd_last(asm_data->syntax_row, synt_row);
	else
		asm_data->syntax_row = synt_row;
	if (ASM_NUM_LABEL)
		ft_merge_in_ecstasy(asm_data, row);
	MACHINE_SYNT_ROW = 1;
}

void	ft_start_fill_rows(t_asm_data *asm_data, t_list *token_chain,\
t_list *labels)
{
	t_list			*chain;
	t_list			*label_chain;
	t_token			*token;

	while (token_chain)
	{
		token = (t_token *)(token_chain->content);
		if (token->type == Label)
		{
			MACHINE_VALID_CODE++;
			chain = ft_lstnew(NULL, 0);
			label_chain = labels;
			while (label_chain && label_chain->content_size != g_label_num)
				label_chain = label_chain->next;
			chain->content = (t_label_compile *)(label_chain->content);
			ft_add_chain_in_list(asm_data, chain);
			g_label_num++;
			ASM_NUM_LABEL++;
		}
		else
			ft_fill_strings(asm_data, token, labels);
		token_chain = token_chain->next;
	}
}

void	ft_check_syntax(t_asm_data *asm_data)
{
	t_token		*token;
	t_list		*labels;
	t_list		*token_chain;

	if (ASM_TOKEN_SIZE < 2)
		return ;
	g_ops = ft_table_operations_init();
	labels = ft_collect_labels(asm_data, 0, 0);
	token_chain = ASM_TOKENS;
	token = (t_token *)(token_chain->content);
	while (token_chain && (TKN_TYPE == Newline || TKN_TYPE == Whitespace))
	{
		token_chain = token_chain->next;
		token = (token_chain) ? (t_token *)(token_chain->content) : NULL;
	}
	ft_start_fill_rows(asm_data, token_chain, labels);
	ft_check_syntax_rows(asm_data, asm_data->syntax_row);
	if (ASM_NUM_LABEL)
		ft_clear_label_temp(asm_data);
	ASM_LABEL = labels;
	ft_solve_rows_values(asm_data, 0, 192);
	g_label_num = 0;
	free(g_ops);
	g_ops = NULL;
}
