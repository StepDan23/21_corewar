/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:29:58 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/21 19:05:12 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*ft_add_magic_header(char *str, int *i)
{
	char	*hex_str;
	char	*new_str;
	int		len;
	int		j;

	j = 0;
	hex_str = ft_base_convert(HEXBASE, COREWAR_EXEC_MAGIC);
	len = ft_strlen(hex_str);
	while (*i + len < 8)
	{
		str[*i] = '0';
		(*i)++;
	}
	while (hex_str[j])
	{
		str[*i] = hex_str[j];
		j++;
		(*i)++;
		if (*i % 100000 == 0)
			str = ft_str_realloc(str, *i);
	}
	return (str);
}

void	ft_conver_word(char *str, int *i, int letter)
{
	char	*hex;
	int		len;

	hex = ft_base_convert(HEXBASE, letter);
	len = ft_strlen(hex);
	if (len == 2)
	{
		str[(*i)++] = hex[0];
		str[(*i)++] = hex[1];
	}
	else
	{
		str[(*i)++] = '0';
		str[(*i)++] = hex[0];
	}
	free(hex);
}

char	*ft_add_name(t_asm_data *asm_data, char *str, int *i, int j)
{
	char	*hex;
	int		len;

	while (CHAMP_NAME[++j])
		ft_conver_word(str, i, CHAMP_NAME[j]);
	j += j;
	while (j < PROG_NAME_LENGTH * 2)
	{
		str[(*i)++] = '0';
		j++;
	}
	return (str);
}

char	*ft_add_null(char *str, int *i)
{
	int		j;

	j = 0;
	while (j < 8)
	{
		str[*i] = '-';
		(*i)++;
		j++;
	}
	return (str);
}

char	*ft_add_comment(t_asm_data *asm_data, char *str, int *i, int j)
{
	char	*hex;
	int		len;

	while (CHAMP_COMMENT[++j])
		ft_conver_word(str, i, CHAMP_COMMENT[j]);
	j += j;
	while (j < COMMENT_LENGTH * 2)
	{
		str[(*i)++] = '0';
		j++;
	}
	return (str);
}
