/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/31 23:11:14 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "vm.h"
#include "libft/libft.h"

int		read_magic(int fd)
{
	int				ret;
	unsigned char	octs[4];
	int				magic;

	if (!(ret = read(fd, octs, sizeof(unsigned char) * 4)))
		return (0);
	magic = (octs[0] << 24) | (octs[1] << 16) | (octs[2] << 8) | octs[3];
	return (magic);
}

char	*read_name(int fd, t_champion *champ)
{

	return (NULL);
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
	// champ->name = read_name(fd);
	return (1);
}

int		main(int argc, char *argv[])
{
	int	chapm;
	// t_champion	*ch;

	chapm = read_champ(argv[1], NULL);
	return (0);
}
