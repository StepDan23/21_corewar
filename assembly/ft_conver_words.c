/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conver_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:29:58 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:08:56 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	ft_add_magic_header(int fd, int *i)
{
	int		temp;

	temp = (COREWAR_EXEC_MAGIC & 0xff000000) >> 24;
	ft_putchar_fd(temp, fd);
	temp = (COREWAR_EXEC_MAGIC & 0xff0000) >> 16;
	ft_putchar_fd(temp, fd);
	temp = (COREWAR_EXEC_MAGIC & 0xff00) >> 8;
	ft_putchar_fd(temp, fd);
	temp = (COREWAR_EXEC_MAGIC & 0xff);
	ft_putchar_fd(temp, fd);
	(*i) += 8;
}

void	ft_add_name(t_asm_data *asm_data, int fd, int *i, int j)
{
	while (CHAMP_NAME[++j])
		ft_add_one_bite(fd, i, CHAMP_NAME[j]);
	j += j;
	while (j < PROG_NAME_LENGTH * 2)
	{
		ft_putchar_fd(0, fd);
		(*i) += 2;
		j += 2;
	}
}

void	ft_add_null(int *i, int fd)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		ft_putchar_fd(0, fd);
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
		ft_putchar_fd(0, fd);
		(*i) += 2;
		j += 2;
	}
}
