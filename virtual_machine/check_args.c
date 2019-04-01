#include "vm.h"
#include "libft.h"

// int		check_args(int ac, char **av, t_vm *vm)
// {
// 	int		count;
// 	int		j;

// 	j = 1;
// 	count = 0;
// 	while (j < ac)
// 	{
// 		if (av[j][0] == '-')
// 			return (0);
// 		j++;
// 	}
// }

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
