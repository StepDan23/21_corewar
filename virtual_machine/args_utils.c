/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:08:33 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/25 18:23:05 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

void	number_format_err(char *param)
{
	ft_printf("-n parameter isn't number. %s\n", param);
	exit(1);
}

void	ivalid_number_err(char *param)
{
	ft_printf("-n invalid number for champion %s.\n", param);
	exit(1);
}

void	same_number_err(void)
{
	ft_printf("There is champion with same number.\n");
	exit(1);
}

int		get_extra_args(int argc, char *argv[], t_vm *vm)
{
	int	i;

	i = 1;
	if (argc <= 1)
		print_help();
	while (ft_strequ(argv[i], "-s") || ft_strequ(argv[i], "--help"))
	{
		if (ft_strequ(argv[i], "-s"))
			vm->bit_flags ^= 1;
		else if (ft_strequ(argv[i], "--help"))
		{
			print_help();
			exit(0);
		}
		i++;
	}
	return (i);
}
