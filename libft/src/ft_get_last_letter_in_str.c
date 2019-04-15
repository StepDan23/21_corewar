/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_letter_in_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:44:50 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/10 21:47:46 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_get_last_letter_in_str(char *str)
{
	char	letter;

	if (!str)
		return (0);
	while(*str)
	{
		letter = *str;
		str++;
	}
	return (letter);
}
