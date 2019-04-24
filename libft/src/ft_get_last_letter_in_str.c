/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_letter_in_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:15:59 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 18:16:00 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_get_last_letter_in_str(char *str)
{
	char	letter;

	if (!str)
		return (0);
	while (*str)
	{
		letter = *str;
		str++;
	}
	return (letter);
}
