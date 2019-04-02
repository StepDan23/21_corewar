/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/02 19:58:13 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

int		main(int argc, char *argv[])
{
	t_vm		*vm;

	vm = vm_new(0);
	while (argc > 1)
	{
		champions_add(argv[argc - 1], 1, &vm->champion);
		argc--;
	}
	read_all_champs(vm->champion);
	vm_spread_champs(vm, vm->champion);
	vm_dump_memory(vm->memory);
	free(vm);
	return (0);
}
