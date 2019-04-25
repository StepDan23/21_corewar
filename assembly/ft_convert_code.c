/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:08:15 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:23:14 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_code_size(t_asm_data *asm_data, int fd, int *i)
{
	int		temp;

	temp = (ASM_CODE_SIZE & 0xff000000) >> 24;
	ft_putchar_fd(temp, fd);
	temp = (ASM_CODE_SIZE & 0xff0000) >> 16;
	ft_putchar_fd(temp, fd);
	temp = (ASM_CODE_SIZE & 0xff00) >> 8;
	ft_putchar_fd(temp, fd);
	temp = (ASM_CODE_SIZE & 0xff);
	ft_putchar_fd(temp, fd);
	(*i) += 8;
}

void	ft_row_compile(t_asm_data *asm_data, t_syntax_row *row, int fd,\
int *i)
{
	int		j;

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
			ft_add_label(asm_data, row, j, fd);
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
