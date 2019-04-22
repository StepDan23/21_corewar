/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:29:58 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 17:09:27 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_magic_header(int fd, int *i)
{
	char	*hex_str;
	int		len;
	int		j;

	j = 0;
	hex_str = ft_base_convert(HEXBASE, COREWAR_EXEC_MAGIC);
	len = ft_strlen(hex_str);
	while (*i + len < 8)
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd('0', fd);
		(*i)++;
	}
	while (hex_str[j])
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd(hex_str[j++], fd);
		(*i)++;
	}
}

void	ft_add_name(t_asm_data *asm_data, int fd, int *i, int j)
{
	while (CHAMP_NAME[++j])
		ft_add_one_bite(fd, i, CHAMP_NAME[j]);
	j += j;
	while (j < PROG_NAME_LENGTH * 2)
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd('0', fd);
		(*i)++;
		j++;
	}
}

void	ft_add_null(int *i, int fd)
{
	int		j;

	j = 0;
	while (j < 8)
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd('-', fd);
		(*i)++;
		j++;
	}
}

void	ft_add_comment(t_asm_data *asm_data, int fd, int *i, int j)
{
	while (CHAMP_COMMENT[++j])
		ft_add_one_bite(fd, i, CHAMP_COMMENT[j]);
	j += j;
	while (j < COMMENT_LENGTH * 2)
	{
		ft_add_space_or_newline(fd, i);
		ft_putchar_fd('0', fd);
		(*i)++;
		j++;
	}
}
