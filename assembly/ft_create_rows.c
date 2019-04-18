/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:04:23 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/18 20:21:03 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_token_type_value(t_types value)
{
	int		res;

	if (value == Register)
		res = T_REG;
	else if (value == Direct_number || value == Direct_label)
		res = T_DIR;
	else if (value == Number || value == Label_arg)
		res = T_IND;
	else
		ft_printf("Strange type of arg = %d\n", value);
	return (res);
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
