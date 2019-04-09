#include "vm.h"
#include "libft.h"
#include <stdlib.h>

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

int		check_args(int ac, char **av, t_vm *vm)
{
	int			number;
	int			count;
	int			j;

	j = 1;
	vm->champion_count = champion_count(ac, av);
	number = 1;
	while (j < ac)
	{
		if (av[j][0] == '-')
		{
			if (j + 1 < ac)
				manage_flag(vm, av[j], av[j + 1], &count);
			j += 2;
		}
		if (j > ac)
			return (0);
		if (check_filename(av[j]))
			champions_add(av[j], count, &vm->champion);
		else
			return (0);
		count = count_avaliable(vm);
		j++;
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
	return (0);
}

int		check_dump(t_vm *vm, char *param)
{
	int		i;

	i = 0;
	if (!is_all_digit(param))
	{
		ft_printf("Dump cycles isn't correct number.\n");
		exit(1);
	}
	ft_atoi(param) > 0 ? vm->dump = ft_atoi(param) : exit(1);
	vm->cycles_to_dump = vm->dump;
	return (1);
}

int		check_n(t_vm *vm, char *param, int *next_number)
{
	t_champion	*champ;
	int			n;

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
	// n > 0 ? n *= -1 : n;
	champ = vm->champion;
	while (champ)
	{
		if (champ->id == (unsigned int)n)
		{
			ft_printf("There is champion with same number.\n");
			exit(1);
		}
		champ = champ->next;
	}
	*next_number = n;
	return (1);
}

int		manage_flag(t_vm *vm, char *flag, char *param, int *count)
{
	if (ft_strequ(flag, "-dump"))
	{
		if (check_dump(vm, param))
			return (1);
		return (0);
	}
	else if (ft_strequ(flag, "-n"))
	{
		if (check_n(vm, param, count))
			return (1);
		return (0);
	}
	ft_printf("Undefined flag.\n");
	exit(1);
}
