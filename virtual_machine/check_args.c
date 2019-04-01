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
#include <stdio.h>
int main(void)
{
	if (!check_filename(".cor"))
		printf("1) %s :			ok\n", ".cor");
	if (check_filename("1.cor"))
		printf("2) %s :			ok\n", "1.cor");
	if (check_filename(".cor.cor"))
		printf("3) %s :			ok\n", ".cor.cor");
	if (check_filename("champ.cor"))
		printf("4) %s :			ok\n", "champ.cor");
	if (!check_filename("champ.core"))
		printf("5) %s :			ok\n", "champ.core");
	return (0);
}