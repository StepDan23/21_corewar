/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:04:23 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 15:39:39 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

	while (rows)
	{
		row = ((t_syntax_row *)(rows->content));
		if (ROW_COM_NUM == -1)
			continue ;
		if (!ROW_NEWLINE)
			ft_error_token(asm_data, ft_strdup("No Newline in Row "),\
			ROW_NUM, 0, 1);
		if (ROW_CNT_MAX != ROW_CNT_ARG - 1)
			ft_error_token(asm_data, ft_strdup("Wrong count of args "),\
			ROW_NUM, 0, 1);
		rows = rows->next;
		MACHINE_VALID_CODE++;
	}
}

void	ft_fill_row(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if (token->type == Label_arg && ft_check_label_arg(asm_data, token, labels,\
	row))
		return ;
	if (TKN_TYPE == Label_arg || TKN_TYPE == Register || TKN_TYPE ==\
	Direct_label || TKN_TYPE == Direct_number || TKN_TYPE == Number)
		ft_row_args_check(asm_data, token, labels, row);
	PREV_ARG_TYPE = token->type;
}

void	ft_check_row(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if (TKN_TYPE == Separator && PREV_ARG_TYPE == Separator)
	{
		ft_error_token(asm_data, ft_strdup("Extra separator in row "), TKN_ROW,\
		TKN_COL, 1);
		return ;
	}
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
		MACHINE_SYNT_ROW = 0;
		ROW_NEWLINE = 1;
		ROW_WAIT_SEP = 0;
		return ;
	}
	ft_fill_row(asm_data, token, labels, row);
}

void	ft_fill_strings(t_asm_data *asm_data, t_token *token, t_list *labels)
{
	t_syntax_row	*row;
	t_list			*synt_row;

	if (!ASM_SYNTAX_ROW && (TKN_TYPE == Newline || TKN_TYPE == Whitespace))
		return ;
	if (token->type == Command)
	{
		ft_add_new_command_row(asm_data, token, row, labels);
		return ;
	}
	if (!MACHINE_SYNT_ROW && token->type >= 4)
	{
		ft_error_token(asm_data, ft_strjoin(ft_strdup("NO command for arg "),\
		token->str), TKN_ROW, TKN_COL, 1);
		return ;
	}
	if (!ASM_SYNTAX_ROW)
		ASM_SYNTAX_ROW = ft_lstnew(NULL, (sizeof(t_syntax_row)));
	synt_row = ASM_SYNTAX_ROW;
	while (synt_row->next)
		synt_row = synt_row->next;
	row = (t_syntax_row *)(synt_row->content);
	if (ROW_NEWLINE)
		return ;
	ft_check_row(asm_data, token, labels, row);
}
