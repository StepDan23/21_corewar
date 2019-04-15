/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:08:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/15 14:18:18 by how_r_u          ###   ########.fr       */
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

	i = 0;
	current = ERRORS;
	while (i < ERROR_SIZE)
	{
		if (ERROR_FLAG == T_ERROR_TYPE)
			ft_printf("%s see -> %d row: %d col\n", T_ERROR_STR, T_ERROR_ROW, T_ERROR_COL);
		temp = current;
		free(((t_errors *)(temp->content))->error_str);
		free(temp);
		current = current->next;
		i++;
	}
}

void	ft_error_add(t_asm_data *asm_data, char *line, int column, int type)
{
	t_list		*chain;

	chain = ft_lstnew(NULL, sizeof(t_errors));
	if (!ERRORS)
		ERRORS = chain;
	else
		ft_lstadd_last(&ERRORS, chain);
	chain->content = ft_error_init(line, ASM_NUM_ROW, column, type);
	if (ERROR_FLAG == 0)
		ERROR_FLAG = type;
	else
		ERROR_FLAG = (ERROR_FLAG < type) ? type : ERROR_FLAG;
	ERROR_SIZE++;
}

