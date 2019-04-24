/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:58:03 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/22 16:42:46 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "vm.h"

int		read_name(int fd, t_champion *champ)
{
	int		ret;

	ret = read(fd, champ->name, sizeof(unsigned char) * PROG_NAME_LENGTH);
	if (ret >= 0 && ret != PROG_NAME_LENGTH)
		return (0);
	else if (ret < 0)
		print_error_exit(0);
	champ->name[PROG_NAME_LENGTH] = '\0';
	return (1);
}

int		read_comment(int fd, t_champion *champ)
{
	int		ret;

	ret = read(fd, champ->comment, sizeof(unsigned char) * COMMENT_LENGTH);
	if (ret >= 0 && ret != COMMENT_LENGTH)
		return (0);
	else if (ret < 0)
		print_error_exit(0);
	champ->comment[COMMENT_LENGTH] = '\0';
	return (1);
}

int		read_botsize(int fd, t_champion *champ)
{
	champ->size = read_4bytes(fd);
	if (!champ->size || champ->size > CHAMP_MAX_SIZE)
		return (0);
	return (1);
}

/*
** Считывает бинарный файл чемпиона
*/

int		read_champ(t_champion *champ)
{
	int	fd;

	fd = open(champ->filename, O_RDONLY);
	if (fd < 0)
		print_error_exit(0);
	if (read_magic(fd) != COREWAR_EXEC_MAGIC)
		print_error_exit(MAGIC_ERR);
	if (!read_name(fd, champ) | !check_null(fd))
		print_error_exit(NAME_ERR);
	if (!read_botsize(fd, champ))
		print_error_exit(CODE_LEN_ERR);
	if (!read_comment(fd, champ) | !check_null(fd))
		print_error_exit(COMM_ERR);
	if (!read_code(fd, champ))
		print_error_exit(CODE_ERR);
	close(fd);
	return (1);
}

void	read_all_champs(t_champion **champs, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		read_champ(champs[i]);
		i++;
	}
}
