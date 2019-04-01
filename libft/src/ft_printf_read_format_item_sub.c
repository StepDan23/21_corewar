/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_format_item_sub.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 22:26:39 by gbrandon          #+#    #+#             */
/*   Updated: 2019/02/08 15:42:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int			fmt_varg_len_set(int *fmt_length, va_list ap)
{
	*fmt_length = va_arg(ap, int);
	return (1);
}

/*
** aAn???
*/

int			fmt_type_set(char *fmt_type, const char it)
{
	char	*type_list;

	type_list = TYPES;
	if (ft_strchr(type_list, it))
	{
		*fmt_type = it;
		return (1);
	}
	return (0);
}

/*
**	fmt_size contains 1 if corresponding size exists in the line
**					  0 - otherwise
**	fmt_size structure: 0zj(ll)l(hh)hL
**	check ll -> j -> z behavior !!!
*/

int			fmt_size_set(char *fms, const char **str)
{
	char	*size_list;

	size_list = SIZES;
	if (ft_strchr(size_list, **str))
	{
		if (**str == 'L')
			*fms = set_bit(*fms, 0);
		else if (**str == 'h')
			*fms = B_SET(*fms, 1) ? s_a_c(*fms, 2, 1) : set_bit(*fms, 1);
		else if (**str == 'l')
			*fms = B_SET(*fms, 3) ? s_a_c(*fms, 4, 3) : set_bit(*fms, 3);
		else if (**str == 'j')
			*fms = set_bit(*fms, 5);
		else if (**str == 'z')
			*fms = set_bit(*fms, 6);
		return (1);
	}
	return (0);
}

const char	*fmt_read_numbers(int *num, const char *str)
{
	long	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (res > 2147483647 || res < -2147483648)
		{
			str++;
			continue;
		}
		res = res * 10 + (*str - 48);
		str++;
	}
	if (res > 2147483647)
		*num = 2147483647;
	else if (res < -2147483648)
		*num = -2147483648;
	else
		*num = res;
	return (str);
}

/*
**	fmt_flags contains 1 in bit if corresponding flag exists
**					   0 - otherwise
**	fmt_flags structure: 000(0)#(space)+-
*/

int			fmt_flag_set(char *fmt_flags, const char it)
{
	char	*flags_list;
	char	*cur_pos;

	flags_list = FLAGS;
	if ((cur_pos = ft_strchr(flags_list, it)))
	{
		*fmt_flags = set_bit(*fmt_flags, cur_pos - flags_list);
		return (1);
	}
	return (0);
}
