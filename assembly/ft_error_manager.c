/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:08:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 17:19:52 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
** Файл для добавления и обработки ошибок
*/

void	ft_print_errors(t_asm_data *asm_data)
{
	int		i;
	t_list	*temp;
	t_list	*current;

	i = -1;
	current = ERRORS;
	while (++i < ERROR_SIZE)
	{
		if (ERROR_FLAG == T_ERROR_TYPE)
		{
			if (ERROR_FLAG == 1)
				ft_putstr("LEXICAL ERROR: ");
			else if (ERROR_FLAG == 2)
				ft_putstr("SYNTAX_ERROR: ");
			(T_ERROR_COL) ? ft_printf("%s: row %d, col %d\n", T_ERROR_STR\
			, T_ERROR_ROW, T_ERROR_COL) : ft_printf("%s: row: %d\n",\
			T_ERROR_STR, T_ERROR_ROW);
		}
		temp = current;
		free(((t_errors *)(temp->content))->error_str);
		free(temp->content);
		current = current->next;
		free(temp);
	}
	(ERROR_SIZE > 0) ? ft_printf("There was ERROR(S). Fix your code\n") : 0;
}

void	ft_error_row_col(t_asm_data *asm_data, char *line, int row, int type)
{
	t_list		*chain;
	t_errors	*error;

	ERROR_SIZE++;
	chain = ft_lstnew(NULL, 0);
	error = ft_error_init(line, row, 0, type);
	chain->content = error;
	chain->content_size = ERROR_SIZE;
	if (!ERRORS)
		ERRORS = chain;
	else
		ft_lstadd_last(ERRORS, chain);
	if (ERROR_FLAG == 0)
		ERROR_FLAG = type;
	else
		ERROR_FLAG = (ERROR_FLAG < type) ? ERROR_FLAG : type;
}

void	ft_error_token(t_asm_data *asm_data, char *line, t_token *token,\
int type)
{
	t_list		*chain;
	t_errors	*error;

	ERROR_SIZE++;
	chain = ft_lstnew(NULL, 0);
	error = ft_error_init(line, token->row, token->col, type);
	chain->content = error;
	chain->content_size = ERROR_SIZE;
	if (!ERRORS)
		ERRORS = chain;
	else
		ft_lstadd_last(ERRORS, chain);
	if (ERROR_FLAG == 0)
		ERROR_FLAG = type;
	else
		ERROR_FLAG = (ERROR_FLAG < type) ? ERROR_FLAG : type;
}

void	ft_error_add(t_asm_data *asm_data, char *line, int column, int type)
{
	t_list		*chain;
	t_errors	*error;

	ERROR_SIZE++;
	chain = ft_lstnew(NULL, 0);
	error = ft_error_init(line, ASM_NUM_ROW, column, type);
	chain->content = error;
	chain->content_size = ERROR_SIZE;
	if (!ERRORS)
		ERRORS = chain;
	else
		ft_lstadd_last(ERRORS, chain);
	if (ERROR_FLAG == 0)
		ERROR_FLAG = type;
	else
		ERROR_FLAG = (ERROR_FLAG < type) ? ERROR_FLAG : type;
}
