/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:04:23 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 12:55:19 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_token_type_value(t_types value)
{
	int		res;

	if (value == Register)
		res = T_REGS;
	else if (value == Direct_number || value == Direct_label)
		res = T_DIRS;
	else if (value == Number || value == Label_arg)
		res = T_INDS;
	else
		ft_printf("Strange type of arg = %d\n", value);
	return (res);
}

int		ft_check_label_arg(t_asm_data *asm_data, t_token *token,\
t_list *labels, t_syntax_row *row)
{
	t_list	*current;
	char	*str;
	int		i;

	str = &TKN_STR[1];
	current = labels;
	ft_printf("list of labels:\n");
	while (current)
	{
		i = 0;
		while (str[i] == LABEL_TEXT[i] && str[i] && LABEL_TEXT[i] != ':')
			i++;
		if (!str[i] && LABEL_TEXT[i] == ':')
			return (0);
		current = current->next;
	}
	ft_error_token(asm_data, ft_strjoin_orig("Label argument not in Label's \
list ", TKN_STR), TKN_ROW, TKN_COL, 1);
	ROW_CNT_ARG++;
	return (1);
}

void	ft_check_syntax_rows(t_asm_data *asm_data, t_list *rows)
{
	t_syntax_row	*row;

	int				i;

	while (rows)
	{
		row = ((t_syntax_row *)(rows->content));
		if (!ROW_NEWLINE)
			ft_error_token(asm_data, ft_strdup("No Newline in Row "),\
			ROW_NUM, 0, 1);
		if (ROW_CNT_MAX != ROW_CNT_ARG - 1)
			ft_error_token(asm_data, ft_strdup("Wrong count of args "),\
			ROW_NUM, 0, 1);
		ft_putstr("Test: \n");
		i = -1;
		while (++i < ROW_CNT_ARG - 1)
			ft_printf("%s ",( ROW_ARGS_TEXT[i]) ? ROW_ARGS_TEXT[i] : "NULL");
		ft_printf("\nCurrent count = %d, estimated count = %d, arg_code = %d\n", ROW_CNT_ARG - 1, ROW_CNT_MAX, ROW_ARG_CODE);
		ft_printf("str num = %d\n", ROW_NUM);
		rows = rows->next;
		MACHINE_VALID_CODE++;
	}
}

void	ft_fill_row(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if (TKN_TYPE == Newline && PREV_ARG_TYPE == Separator &&\
	(ROW_CNT_ARG - 1 <= ROW_CNT_MAX))
	{
		ROW_NEWLINE = 1;
		ft_error_token(asm_data, ft_strdup("Separator before Newline "),\
		TKN_ROW, TKN_COL, 1);
		return ;
	}
	if (ROW_WAIT_SEP && TKN_TYPE == Separator)
		ROW_WAIT_SEP = 0;
	if (TKN_TYPE == Newline)
	{
		ROW_NEWLINE = 1;
		ROW_WAIT_SEP = 0;
		return ;
	}
	if (token->type == Label_arg && ft_check_label_arg(asm_data, token, labels,\
	row))
		return ;
	if (TKN_TYPE == Label_arg || TKN_TYPE == Register || TKN_TYPE ==\
	Direct_label || TKN_TYPE == Direct_number || TKN_TYPE == Number)
		ft_row_args_check(asm_data, token, labels, row);
	PREV_ARG_TYPE = token->type;
}

void	ft_fill_strings(t_asm_data *asm_data, t_token *token, t_list *labels)
{
	t_syntax_row	*row;
	t_list			*synt_row;

	if (!asm_data->syntax_row && (TKN_TYPE == Newline ||\
	TKN_TYPE == Whitespace))
		return ;
	if (token->type == Command)
		ft_add_new_command_row(asm_data, token, row);
	if (!asm_data->syntax_row)
		asm_data->syntax_row = ft_lstnew(NULL, (sizeof(t_syntax_row)));
	synt_row = asm_data->syntax_row;
	while (synt_row->next)
		synt_row = synt_row->next;
	row = (t_syntax_row *)(synt_row->content);
	if (ROW_NEWLINE)
		return ;
	if (TKN_TYPE == Separator && PREV_ARG_TYPE == Separator)
	{
		ft_error_token(asm_data, ft_strdup("Extra separator in row "), TKN_ROW,\
		TKN_COL, 1);
		return ;
	}
	ft_fill_row(asm_data, token, labels, row);
}
