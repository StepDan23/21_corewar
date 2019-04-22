/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:08:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 21:20:57 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_code_size(t_asm_data *asm_data, int fd, int *i)
{
	int		j;
	int		len;
	char	*hex;

	hex = ft_base_convert(HEXBASE, ASM_CODE_SIZE);
	len = ft_strlen(hex);
	j = 0;
	while (8 - j - len > 0)
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd('0', fd);
		(*i)++;
		j++;
	}
	j = 0;
	while (hex[j])
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd(hex[j], fd);
		(*i)++;
		j++;
	}
	free(hex);
}

void	ft_row_compile(t_asm_data *asm_data, t_syntax_row *row, int fd,\
int *i)
{
	int		j;
	char	*temp;

	j = 0;
	ft_add_one_bite(fd, i, ROW_COM_NUM + 1);
	if (ROW_ARG_CODE)
		ft_add_one_bite(fd, i, ROW_ARG_CODE);
	while (j < ROW_CNT_MAX)
	{
		if (ROW_ARG_TYPES[j] == Register)
			ft_add_register(row, fd, i, j);
		else if (ROW_ARG_TYPES[j] == Direct_label ||\
		ROW_ARG_TYPES[j] == Label_arg)
		{
			temp = ft_add_label(asm_data, row, j);
			ft_write_arg_text(fd, ROW_ARGS_SIZES[j], temp, i);
		}
		else if (ROW_ARG_TYPES[j] == Direct_number)
			ft_add_direct_number(row, fd, i, j);
		else if (ROW_ARG_TYPES[j] == Number)
			ft_add_number_code(row, fd, i, j);
		j++;
	}
	ASM_CODE_ITER += ROW_CODE_SIZE;
}

void	ft_code_compile(t_asm_data *asm_data, int fd, int *i)
{
	t_list			*chain_row;
	t_syntax_row	*row;

	chain_row = ASM_SYNTAX_ROW;
	while (chain_row)
	{
		row = (t_syntax_row *)(chain_row->content);
		ft_row_compile(asm_data, row, fd, i);
		chain_row = chain_row->next;
	}
}
