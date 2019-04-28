/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:56:40 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 20:34:20 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_word_size(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int		ft_word_num(char *str, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j++;
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (j);
}

static void		ft_gen_res(char ***arr, char *str, int c, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (str[i])
	{
		(*arr)[k] = malloc(1 + ft_word_size(&(str[i]), c));
		while (str[i] && str[i] != c)
		{
			(*arr)[k][j] = str[i];
			i++;
			j++;
		}
		(*arr)[k][j] = 0;
		while (str[i] && str[i] == c)
			i++;
		k++;
		j = 0;
	}
	(k >= 0) ? (*arr)[k] = 0 : 0;
}

char			**ft_strsplit(char const *str, char c)
{
	size_t	i;
	char	**new_arr;

	if ((void *)str == 0x0)
		return (NULL);
	i = 0;
	while (*str == c)
		str++;
	new_arr = malloc(8 * (ft_word_num((char *)str, c) + 1));
	if (!new_arr)
		return (0);
	ft_gen_res(&new_arr, (char *)str, c, 0);
	return (new_arr);
}
