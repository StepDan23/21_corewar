#include "vm.h"
#include "libft.h"

int		is_all_digit(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		count_avaliable(t_vm *vm)
{
	t_champion		*tmp;
	unsigned int	count;

	count = 1;
	tmp = vm->champion;
	if (tmp == NULL)
		return (count);
	while (count)
	{
		while (tmp)
		{
			if (tmp->id == count)
			{
				tmp = vm->champion;
				count++;
				continue;
			}
			tmp = tmp->next;
		}
		return (count);
	}
	return (count);
}
