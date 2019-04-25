/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:07:44 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:24:51 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_write_arg_text(int fd, int size, char *hex, int *i)
{
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(hex);
	while (j < 2 * size - len)
	{
		ft_putchar_fd(0, fd);
		(*i)++;
		j++;
	}
	j = 0;
	while (hex[j])
	{
		ft_putchar_fd(hex[j++], fd);
		(*i)++;
	}
	free(hex);
}

void	ft_add_number_code(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;
	int		size;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(ROW_ARGS_TEXT[j]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	if (size == 4)
		ft_putchar_fd((value & 0xff000000) >> 24, fd);
	if (size >= 3)
		ft_putchar_fd((value & 0xff0000) >> 16, fd);
	if (size >= 2)
		ft_putchar_fd((value & 0xff00) >> 8, fd);
	if (size >= 1)
		ft_putchar_fd((value & 0xff), fd);
}

void	ft_add_direct_number(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;
	int		size;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	if (size == 4)
		ft_putchar_fd((value & 0xff000000) >> 24, fd);
	if (size >= 3)
		ft_putchar_fd((value & 0xff0000) >> 16, fd);
	if (size >= 2)
		ft_putchar_fd((value & 0xff00) >> 8, fd);
	if (size >= 1)
		ft_putchar_fd((value & 0xff), fd);
}

void	ft_add_register(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;

	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	(*i)++;
	ft_putchar_fd(value, fd);
}

char	*ft_add_label(t_asm_data *asm_data, t_syntax_row *row, int j, int fd)
{
	int		value;
	int		size;

	size = ROW_ARGS_SIZES[j];
	value = ft_get_label_value(asm_data, ROW_ARGS_TEXT[j]);
	value = value - ASM_CODE_ITER;
	if (value < 0)
		value = ft_get_negative_value(value, size);
	if (size == 4)
		ft_putchar_fd((value & 0xff000000) >> 24, fd);
	if (size >= 3)
		ft_putchar_fd((value & 0xff0000) >> 16, fd);
	if (size >= 2)
		ft_putchar_fd((value & 0xff00) >> 8, fd);
	if (size >= 1)
		ft_putchar_fd((value & 0xff), fd);
	return (NULL);
}
