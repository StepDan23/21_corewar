/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:07:44 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 16:21:59 by lshanaha         ###   ########.fr       */
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
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd(0, fd);
		(*i)++;
		j++;
	}
	j = 0;
	while (hex[j])
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd(hex[j++], fd);
		(*i)++;
	}
	free(hex);
}

void	ft_add_number_code(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;
	int		size;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(ROW_ARGS_TEXT[j]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	hex = ft_int_base_convert(HEXBASE, value);
	ft_write_arg_text(fd, size, hex, i);
}

void	ft_add_direct_number(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;
	int		size;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	hex = ft_int_base_convert(HEXBASE, value);
	ft_write_arg_text(fd, size, hex, i);
}

void	ft_add_register(t_syntax_row *row, int fd, int *i, int j)
{
	int		value;
	int		size;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	hex = ft_int_base_convert(HEXBASE, value);
	ft_write_arg_text(fd, size, hex, i);
}

char	*ft_add_label(t_asm_data *asm_data, t_syntax_row *row, int j)
{
	int		value;
	int		size;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_get_label_value(asm_data, ROW_ARGS_TEXT[j]);
	value = value - ASM_CODE_ITER;
	if (value < 0)
		value = ft_get_negative_value(value, size);
	hex = ft_int_base_convert(HEXBASE, value);
	return (hex);
}
