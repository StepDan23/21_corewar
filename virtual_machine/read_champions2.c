/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:02:16 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/03 00:36:49 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "vm.h"
#include "libft.h"

/*
** Выводит сообщение об ошибке и завершает программу.
** Коды ошибок объявленны в vm.h
*/

void	print_error_exit(int code)
{
	if (code == MAGIC_ERR)
		ft_printf("Error: Wrong magic\n");
	else if (code == NAME_ERR)
		ft_printf("Error: Wrong name format\n");
	else if (code == COMM_ERR)
		ft_printf("Error: Wrong comment format\n");
	else if (code == CODE_ERR)
		ft_printf("Error: Wrong code format\n");
	else if (code == CODE_LEN_ERR)
		ft_printf("Error: Wrong code lenght format\n");
	else
		ft_printf("Error: %s\n", strerror(errno));
	exit(0);
}

/*
** Читает из файла 4 байта данных
** 4 т.к magic, null, bot_size занимает 4 байта.
*/

int		read_4bytes(int fd)
{
	int				ret;
	unsigned char	octs[4];
	int				total;

	ret = read(fd, octs, sizeof(unsigned char) * 4);
	if (ret >= 0 && ret != 4)
		return (0);
	else if (ret < 0)
		print_error_exit(0);
	total = (octs[0] << 24) | (octs[1] << 16) | (octs[2] << 8) | octs[3];
	return (total);
}

int		check_null(int fd)
{
	int		total;

	total = read_4bytes(fd);
	return (total == 0);
}

int		read_magic(int fd)
{
	return (read_4bytes(fd));
}

int		read_code(int fd, t_champion *champ)
{
	int		ret;

	champ->code = (unsigned char *)malloc(sizeof(unsigned char) * champ->size);
	if (!champ->code)
		print_error_exit(0);
	ret = read(fd, champ->code, champ->size);
	if (ret > 0 && ret != (int)champ->size)
		return (0);
	else if (ret < 0)
		print_error_exit(0);
	if (read(fd, champ->code, 1))
		return (0);
	return (1);
}
