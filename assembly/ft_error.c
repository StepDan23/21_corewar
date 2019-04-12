/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:08:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/12 20:38:06 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
** Файл для добавления и обработки ошибок
*/

void	ft_error_chain_init(t_error *error_chain)
{
	error_chain->num_column = 0;
	error_chain->num_str = 0;
	error_chain->type_of_error = 0;
	error_chain->str = NULL;
}

char	*ft_lexical_error_str(char *str, int num_str, int num_column)
{
	char	*res;
	int		len;

	//printf("str ======= %s\n",str);
	len = ft_strlen(str) + ft_intlen(num_str) + ft_intlen(num_column);
	res = ft_strnew(len + 55);
	//ft_printf("kjsdhfjds\n");
	ft_sprintf(res, "ERROR: Lexical error at [%3d str, %3d cloumn], str = %s\n"\
	,num_str, num_column, str);
	//ft_printf("res = %s\n", res);
	return (res);
}

char	*ft_syntax_error_swtr(char *str, int num_str, int num_column)
{
	char	*res;

	ft_sprintf(res, "sdgdsgsdg\n", str, num_str,num_column);
	return (res);
}

char	*ft_semantic_error_str(char *str, int num_str, int num_column)
{
	char	*res;

	ft_sprintf(res, "Semantic error\n", str, num_str,num_column);
	return (res);
}

void	ft_error_add(t_asm *asm_data, char *str, int column, int error_type)
{
	t_error		*error_chain;
	t_list		*chain;
	char		*error_str;

	chain = ft_lstnew(NULL, sizeof(t_error));
	if (!ERROR_LIST)
		ERROR_LIST = chain;
	else
		ft_lstadd_last(&ERROR_LIST, chain);

	error_chain = (t_error *)(chain->content);
	ft_error_chain_init(error_chain);
	chain->content = error_chain;
	ERROR_NUM_STR = STR_NUM;
	ERROR_NUM_COLUMN = column;
	ERROR_TYPE = error_type;
	if (error_type == 1)
		error_str = ft_lexical_error_str(str, STR_NUM, column);
	else if (error_type == 2)
		error_str = ft_syntax_error_swtr(str, STR_NUM, column);
	else
		error_str = ft_semantic_error_str(str, STR_NUM, column);
	ERROR_STR = error_str;
	ft_printf("error message = %s\n", ERROR_STR);
	ERROR_LIST_SIZE++;
}