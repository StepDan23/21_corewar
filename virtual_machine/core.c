/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:12:51 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/01 22:54:45 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

int		main(int argc, char *argv[])
{
	int	is_valid;
	t_champion	*ch;
	t_vm		*vm;

	ch = new_champ(1, argv[argc - 1]);
	is_valid = read_champ(ch);
	if (!is_valid)
		exit(0);
	vm = vm_new(0);
	vm_load_champ(vm, ch, 0);
	vm_dump_memory(vm->memory);
	free(vm);
	return (0);
}
