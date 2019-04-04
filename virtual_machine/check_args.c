#include "vm.h"
#include "libft.h"

// TODO  Manage flags
// TODO: manage -n flag
int		check_args(int ac, char **av, t_vm *vm)
{
	int			count;
	int			j;
	t_champion	*tmp;

	j = 1;
	count = 0;
	tmp = vm->champion;
	while (j < ac)
	{
		if (av[j][0] == '-')
		{
			if (j + 1 < ac)
				manage_flag(vm, av[j], ac[j + 1], &count);
			j += 2;
		}
		if (check_filename(av[j]))
			champions_add(av[j], ++count, &vm->champion, &tmp);
		else
			return (0);
		j++;
	}
	return (1);
}

int		check_filename(char *file)
{
	int		len;

	len = ft_strlen(file);
	if (len > 4)
	{
		if (ft_strnequ(&file[len - 4], ".cor", 4))
			return (1);
	}
	return (0);
}
// TODO 1. Test check_dump
int		check_dump(t_vm *vm, char param)
{
	int		i;

	i = 0;
	if (!is_all_digit(param))
	{
		ft_printf("Dump cycles isn't number.\n");
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
		ft_printf("-n parametr isn't number.\n");
		exit(1);
	}
	n = ft_atoi(param);
	n > 0 ? n *= -1 : n;
	champ = vm->champion;
	while (champ)
	{
		if (champ->id = n)
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
