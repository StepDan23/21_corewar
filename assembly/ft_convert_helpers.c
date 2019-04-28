/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:10:16 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 17:56:35 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_one_bite(int fd, int *i, int value)
{
	char	*hex;
	int		len;

	ft_putchar_fd(value, fd);
	(*i) += 2;
}

int		ft_get_negative_value(int value, long size)
{
	value = -value;
	value = ~value;
	value = value + 1;
	size = ft_power(256, size) - 1;
	value = (int)(value & size);
	return (value);
}

int		ft_get_label_value(t_asm_data *asm_data, char *label_arg)
{
	int				value;
	int				i;
	t_list			*current;
	t_label_compile	*label;

	value = 0;
	label_arg = &label_arg[2];
	current = ASM_LABEL;
	while (current)
	{
		i = 0;
		label = ((t_label_compile *)(current->content));
		while (label_arg[i] && LABEL_TEXT[i] && label_arg[i] == LABEL_TEXT[i]\
		&& LABEL_TEXT[i] != LABEL_CHAR)
			i++;
		if (!label_arg[i] && LABEL_TEXT[i] == LABEL_CHAR)
		{
			if (label->points_to_row == -5)
				return (ASM_CODE_SIZE);
			else
				return (label->row->code_place);
		}
		current = current->next;
	}
	return (value);
}
