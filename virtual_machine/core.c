/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/31 23:51:35 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "vm.h"
#include "libft/libft.h"

int		read_4bytes(int fd)
{
	int				ret;
	unsigned char	octs[4];
	int				total;

	if (!(ret = read(fd, octs, sizeof(unsigned char) * 4)))
		return (0);
	total = (octs[0] << 24) | (octs[1] << 16) | (octs[2] << 8) | octs[3];
	return (total);
}

int		read_magic(int fd)
{
	return (read_4bytes(fd));
}

int		read_name(int fd, t_champion *champ)
{
	int		ret;

	if (!(ret = read(fd, champ->name, sizeof(unsigned char) * PROG_NAME_LENGTH)))
		return (0);
	champ->name[PROG_NAME_LENGTH - 1] = '\0';
	return (1);
}

int		read_comment(int fd, t_champion *champ)
{
	int		ret;

	if (!(ret = read(fd, champ->comment, sizeof(unsigned char) * COMMENT_LENGTH)))
		return (0);
	champ->name[COMMENT_LENGTH - 1] = '\0';
	return (1);
}

int		check_null(int fd)
{
	int		total;

	total = read_4bytes(fd);
	return (total == 0);
}

int		read_botsize(int fd, t_champion *champ)
{
	champ->size = read_4bytes(fd);
	if (!champ->size || champ->size > CHAMP_MAX_SIZE)
		return (0);
	return (1);
}

int		read_code(int fd, t_champion *champ)
{
	int		ret;

	champ->code = (unsigned char *)malloc(sizeof(unsigned char) * champ->size);
	if (!(ret = read(fd, champ->code, champ->size)))
		return (0);
	if (read(fd, champ->code, 1))
		return (0);
	return (1);
}

int		read_champ(char *filename, t_champion *champ)
{
	int				fd;
	int				magic;

	if (!(fd = open(filename, O_RDONLY)))
		return (0);
	magic = read_magic(fd);
	ft_printf("%x\n", magic);
	if (magic != COREWAR_EXEC_MAGIC)
		return (0);
	if (!read_name(fd, champ) | !check_null(fd))
		return (0);
	if (!read_botsize(fd, champ))
		return (0);
	if (!read_comment(fd, champ) | !check_null(fd))
		return (0);
	if (!read_code(fd, champ))
		return (0);
	ft_printf("%s\n%s", champ->name, champ->comment);
	return (1);
}

int		main(int argc, char *argv[])
{
	int	chapm;
	// t_champion	*ch;

	chapm = read_champ(argv[1], NULL);
	return (0);
}
