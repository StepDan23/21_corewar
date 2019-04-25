/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:04:23 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 13:05:32 by lshanaha         ###   ########.fr       */
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
	if (TKN_TYPE == Direct_label && *str)
		str = &str[1];
	current = labels;
	while (current)
	{
		i = 0;
		while (str[i] == LABEL_TEXT[i] && str[i] && LABEL_TEXT[i] != LABEL_CHAR)
			i++;
		if (!str[i] && LABEL_TEXT[i] == LABEL_CHAR)
			return (0);
		current = current->next;
	}
	ft_error_token(asm_data, ft_strjoin_orig("Label argument not in Label's \
list ", TKN_STR), token, 3);
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
			ft_error_row_col(asm_data, ft_strdup("No Newline in Row "),\
			ROW_NUM, 2);
		if (ROW_CNT_MAX != ROW_CNT_ARG - 1)
			ft_error_row_col(asm_data, ft_strdup("Wrong count of args "),\
			ROW_NUM, 3);
		rows = rows->next;
		MACHINE_VALID_CODE++;
	}
}

void	ft_fill_row(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if ((TKN_TYPE == Label_arg || TKN_TYPE == Direct_label) &&
	ft_check_label_arg(asm_data, token, labels, row))
	{
		ft_error_token(asm_data, ft_strdup("This label does not exists "),\
		token, 2);
		return ;
	}
	if (TKN_TYPE == Label_arg || TKN_TYPE == Register || TKN_TYPE ==\
	Direct_label || TKN_TYPE == Direct_number || TKN_TYPE == Number)
		ft_row_args_check(asm_data, token, row);
	PREV_ARG_TYPE = token->type;
}

void	ft_check_row(t_asm_data *asm_data, t_token *token, t_list *labels,\
t_syntax_row *row)
{
	if (TKN_TYPE == Separator && PREV_ARG_TYPE == Separator)
	{
		ft_error_token(asm_data, ft_strdup("Extra separator in row "), token,\
		2);
		return ;
	}
	if (TKN_TYPE == Newline && PREV_ARG_TYPE == Separator &&\
	(ROW_CNT_ARG - 1 <= ROW_CNT_MAX))
	{
		ROW_NEWLINE = 1;
		ft_error_token(asm_data, ft_strdup("Separator before Newline "),\
		token, 2);
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
		ft_add_new_command_row(asm_data, token);
		return ;
	}
	if (!MACHINE_SYNT_ROW && token->type >= 4)
	{
		ft_error_token(asm_data, ft_strjoin_orig("NO command for arg ",\
		token->str), token, 2);
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
