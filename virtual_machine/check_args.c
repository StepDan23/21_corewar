#include "vm.h"
#include "libft.h"

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
			j += 2;
			continue;
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
