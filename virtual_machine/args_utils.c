#include "vm.h"
#include "libft.h"

int		is_all_digit(char *str)
{
	if (*str == '-')
		str++;
	while (str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
