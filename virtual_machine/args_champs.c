#include "vm.h"
#include "libft.h"
#include <stdlib.h>

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
		{
			i += 3;
			continue;
		}
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
			if (ft_strequ(av[i], "-n"))
				i++;
			else
				i++;

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
		else
		{
			ft_printf("invalid parameters: -dump [cycles_to_dump].\n");
			exit(1);
		}
	}
	else if (ft_strequ(av[i], "-n"))
	{
		if (i + 2 < ac && is_all_digit(av[i + 1]) && check_filename(av[i + 2]))
			return (1);
		else
		{
			ft_printf("invalid parameters: -n [number] [filename].\n");
			exit(1);
		}
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
		else if ((av[i][0] != '-' && !is_all_digit(av[i])) && !check_filename(av[i]))
		{
			ft_printf("filename %s invalid\n", av[i]);
			return (0);
		}
		i++;
	}
	return (count);
}

