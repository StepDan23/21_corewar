/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:32:50 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/24 15:38:45 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include <stdlib.h>

int		args_read(int ac, char **av, t_vm *vm)
{
	int			j;

	if (ac <= 1)
	{
		ft_printf("[-n][number][filename.cor]|[filename.cor]\n");
		exit(1);
	}
	if (args_check(ac, av))
	{
		vm->champion_count = champion_count(ac, av);
		if (vm->champion_count > MAX_PLAYERS)
		{
			ft_printf("Max players is %d.\n", MAX_PLAYERS);
			exit(1);
		}
		n_champion(ac, av, vm);
		w_champion(ac, av, vm);
		j = 0;
		while (++j < ac)
		{
			if (ft_strequ(av[j], "-dump"))
				manage_flag(vm, av[j], av[j + 1]);
		}
	}
	return (1);
}

int		check_filename(char *file)
{
	int		len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len > 4)
	{
		if (ft_strnequ(&file[len - 4], ".cor", 4))
			return (1);
	}
	ft_printf("invalid filename %s\n", file);
	return (0);
}

int		check_dump(t_vm *vm, char *param)
{
	if (!is_all_digit(param))
	{
		ft_printf("Dump cycles isn't correct number.\n");
		exit(1);
	}
	if (vm->cycles_to_dump != -1)
	{
		ft_printf("Several -dump args forbidden.\n");
		exit(1);
	}
	ft_atoi(param) > 0 ? vm->cycles_to_dump = ft_atoi(param) : exit(1);
	return (1);
}

int		check_n(t_vm *vm, char *param)
{
	t_champion	*champ;
	int			n;
	int			id;

	if (!is_all_digit(param))
		number_format_err(param);
	n = ft_atoi(param);
	if (n > vm->champion_count || n < 1)
		ivalid_number_err(param);
	champ = vm->champion[0];
	id = 0;
	while (id < MAX_PLAYERS)
	{
		if (champ != NULL)
		{
			if (champ->id == n)
				same_number_err();
		}
		champ = vm->champion[++id];
	}
	return (1);
}

int		manage_flag(t_vm *vm, char *flag, char *param)
{
	if (ft_strequ(flag, "-dump"))
	{
		if (check_dump(vm, param))
			return (1);
		return (0);
	}
	else if (ft_strequ(flag, "-n"))
	{
		if (check_n(vm, param))
			return (1);
		return (0);
	}
	ft_printf("Undefined flag.\n");
	exit(1);
}
