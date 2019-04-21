/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:08:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/21 21:15:06 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*ft_add_code_size(t_asm_data *asm_data, char *str, int *i)
{
	int		j;
	int		len;
	char	*hex;

	hex = ft_base_convert(HEXBASE, ASM_CODE_SIZE);
	len = ft_strlen(hex);
	j = 0;
	while (8 - j - len > 0)
	{
		str[(*i)++] = '0';
		j++;
	}
	j = 0;
	while (hex[j])
	{
		str[(*i)++] = hex[j];
		j++;
	}
	free(hex);
	return (str);
}

void	ft_add_label_arg(t_asm_data *asm_data, t_syntax_row *row, char *str, int *i, int j)
{
	int		value;
	int		size;
	int		len;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_get_label_value(asm_data, ROW_ARGS_TEXT[j]);
	ft_printf("value = %d\n", value);
}


char	*ft_row_compile(t_asm_data *asm_data, t_syntax_row *row, char *str,\
int *i)
{
	int		j;

	j = 0;
	ft_add_one_bite(str, i, ROW_COM_NUM + 1, asm_data);
	if (ROW_ARG_CODE)
		ft_add_one_bite(str, i, ROW_ARG_CODE, asm_data);
	while (j < ROW_CNT_MAX)
	{
		//if (ROW_ARG_TYPES[j] == Register)
		//	ft_add_register(asm_data, row, str, i, j);
		if (ROW_ARG_TYPES[j] == Label_arg)
			ft_add_label_arg(asm_data, row, str, i, j);
		//else if (ROW_ARG_TYPES[j] == Direct_label)
		//if (ROW_ARG_TYPES[j] == Direct_number)
		//	ft_add_direct_number(asm_data, row, str, i, j);
		//else if (ROW_ARG_TYPES[j] == Number)
		//	ft_add_number_code(asm_data, row, str, i, j);
		j++;
	}
	return (str);
}

char	*ft_code_compile(t_asm_data *asm_data, char *str, int *i)
{
	t_list			*chain_row;
	t_syntax_row	*row;

	chain_row = ASM_SYNTAX_ROW;
	while (chain_row)
	{
		row = (t_syntax_row *)(chain_row->content);
		ft_row_compile(asm_data, row, str, i);
		chain_row = chain_row->next;
	}
	return (str);
}
