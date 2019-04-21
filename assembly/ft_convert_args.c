/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:07:44 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/21 21:13:12 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_number_code(t_asm_data *asm_data, t_syntax_row *row, char *str, int *i, int j)
{
	int		value;
	int		size;
	int		len;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(ROW_ARGS_TEXT[j]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	hex = ft_int_base_convert(HEXBASE, value);
	len = ft_strlen(hex);
	value = 0;
	while (value < size * 2 - len)
	{
		str[(*i)++] = '0';
		value++;
	}
	value = 0;
	while (hex[value])
	{
		str[(*i)++] = hex[value];
		value++;
	}
	free(hex);
}

void	ft_add_direct_number(t_asm_data *asm_data, t_syntax_row *row, char *str, int *i, int j)
{
	int		value;
	int		size;
	int		len;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	if (value < 0)
		value = ft_get_negative_value(value, size);
	hex = ft_int_base_convert(HEXBASE, value);
	len = ft_strlen(hex);
	ft_printf("value = %d\n", value);
	value = 0;
	while (value < size * 2 - len)
	{
		str[(*i)++] = '0';
		value++;
	}
	value = 0;
	while (hex[value])
	{
		str[(*i)++] = hex[value];
		value++;
	}
	free(hex);
}

void	ft_add_register(t_asm_data *asm_data, t_syntax_row *row, char *str, int *i, int j)
{
	int		value;
	int		size;
	int		len;
	char	*hex;

	size = ROW_ARGS_SIZES[j];
	value = ft_atoi(&(ROW_ARGS_TEXT[j])[1]);
	hex = ft_int_base_convert(HEXBASE, value);
	len = ft_strlen(hex);
	ft_printf("value = %d\n", value);
	value = 0;
	while (value < 2 * size - len)
	{
		str[(*i)++] = '0';
		value++;
	}
	value = 0;
	while (hex[value])
	{
		str[(*i)++] = hex[value];
		value++;
	}
	free(hex);
}


