#include "vm.h"

int		check_args(int ac, char **av, t_vm *vm)
{
	int		count;
	int		j;

	j = 1;
	count = 0;
	while (j < ac)
	{
		if (av[j][0] == '-')
			return (0);
		j++;
	}
}

int		valid_filename(char *file)
{
	int		len;

	len = 0;
	while ()
}