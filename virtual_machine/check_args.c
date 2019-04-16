#include "vm.h"
#include "libft.h"
#include <stdlib.h>

/*
	Определить количество чемпионов +
	Для чемпиона с флагом n установить номер
			Определить чемпиона с флагом и проверить флаг -> установить номер
			Перейти к след. чемпиону с флагом
	Установить остальным чемпионам свободные номера
			Если чесмпион без флага, проверить и установить флаг
			Перейти к след. чемпиону без флага
	Создать последовательный лист чемпионов в голове 4 номер
*/

int		n_champion(int ac, char **av, t_vm *vm)
{
	int			i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-n") && check_n(vm, av[i + 1]))
			champions_add(av[i + 2], ft_atoi(av[i + 1]), vm->champion);
		else if (ft_strequ(av[i], "-n") && !check_n(vm, av[i + 1]))
			exit(1);
		i++;
	}
	return (1);
}

int		w_champion(int ac, char **av, t_vm *vm)
{
	int			i;
	int			num;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-n"))
			i += 3;
		else if (ft_strequ(av[i], "-dump"))
			i += 2;
		if (i < ac)
		{
			num = champion_number(vm->champion);
			champions_add(av[i], num, vm->champion);
		}
		i++;
	}
	return (1);
}

int		args_check(int ac, char **av)
{
	int			i;

	i = 1;
	while(i < ac)
	{
		if (ft_strequ(av[i], "-n") || ft_strequ(av[i], "-dump"))
		{
			if (!flags_check(ac, i, av))
				exit(1);
		}
		else if (!check_filename(av[i]))
			exit(1);
		i++;
	}
	return (1);
}

int		flags_check(int ac, int i, char **av)
{
	if (ft_strequ(av[i], "-dump"))
	{
		if (i + 1 < ac && is_all_digit(av[i + 1]))
			return (1);
		return (0);
	}
	else if (ft_strequ(av[i], "-n"))
	{
		if (i + 2 < ac && is_all_digit(av[i + 1]) && check_filename(av[i + 2]))
			return (1);
		return (0);
	}
	return (0);
}

int		champion_count(int ac, char **av)
{
	int		i;
	int		count;

	count = 0;
	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-' && !is_all_digit(av[i]) && check_filename(av[i]))
			count++;
		else if (av[i][0] != '-' && !is_all_digit(av[i]) && !check_filename(av[i]))
		{
			ft_printf("arg filename %s invalid\n", av[i]);
			exit(1);
		}
		i++;
	}
	return (count);
}

int		args_read(int ac, char **av, t_vm *vm)
{
	int			j;

	if (args_check(ac, av))
	{
		n_champion(ac, av, vm);
		w_champion(ac, av, vm);
		j = 1;
		while (j < ac)
		{
			if (ft_strequ(av[j], "-dump"))
				manage_flag(vm, av[j], av[j + 1]);
			j++;
		}
	}
	return (0);
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
	return (0);
}

int		check_dump(t_vm *vm, char *param)
{
	if (!is_all_digit(param))
	{
		ft_printf("Dump cycles isn't correct number.\n");
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

	n = 0;
	if (!is_all_digit(param))
	{
		ft_printf("-n parametr isn't number. %s\n", param);
		exit(1);
	}
	if ((n = ft_atoi(param)) > vm->champion_count)
	{
		ft_printf("-n parametr is more than the number of champions. %s\n", param);
		exit(1);
	}
	champ = vm->champion[0];
	id = 1;
	while (id <= MAX_PLAYERS)
	{
		if (champ->id == n)
		{
			ft_printf("There is champion with same number.\n");
			exit(1);
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
