/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:10:16 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/21 21:13:27 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_one_bite(char *str, int *i, int value, t_asm_data *asm_data)
{
	char	*hex;
	int		len;

	hex = ft_base_convert(HEXBASE, value);
	len = ft_strlen(hex);
	str[(*i)++] = (len <= 1) ? '0' : hex[0];
	str[(*i)++] = (len <= 1) ? hex[0] : hex[1];
	free(hex);
	ASM_CODE_ITER++;
}

int		ft_get_negative_value(int value, long size)
{
	value = -value;
	//ft_putendl(ft_base_convert("01", value));
	value = ~value;
	value = value | 1;
	//ft_putendl(ft_base_convert("01", value));
	size = ft_power(256, size) - 1;
	value = (int)(value & size);
	//ft_putendl(ft_base_convert("01", value));
	//ft_putendl(ft_int_base_convert(HEXBASE, (int)value));
	return (value);
}

int		ft_get_label_value(t_asm_data *asm_data, char *label_arg)
{
	int				value;
	int				i;
	t_list			*current;
	t_label_compile	*label;

	value = 0;
	label_arg = &label_arg[1];
	current = ASM_LABEL;
	while (current)
	{
		i = 0;
		label = ((t_label_compile *)(current->content));
		while (label_arg[i] && LABEL_TEXT[i] && label_arg[i] == LABEL_TEXT[i]\
		&& LABEL_TEXT[i] != LABEL_CHAR)
			i++;
		if (!label_arg[i] && LABEL_TEXT[i] == LABEL_CHAR)
			return (label->row->code_place);
		current = current->next;
	}
	return (value);
}
