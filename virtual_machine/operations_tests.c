/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:56:09 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/06 17:25:37 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"
#include <assert.h>

int		get_2bytes_test(unsigned char *memory)
{
	int	res;

	memory[0] = 0x42;
	memory[1] = 0x01;
	res = get_2bytes(memory, 0);
	assert(res == 133);

	memory[0] = 0x42;
	memory[4095] = 0x01;
	res = get_2bytes(memory, 4095);
	assert(res == 133);

	memory[44] = 0x42;
	memory[45] = 0x01;
	res = get_2bytes(memory, 44);
	assert(res == 133);
	return (1);
}

int		get_4bytes_test(unsigned char *memory)
{
	int	res;

	memory[0] = 0x42;
	memory[1] = 0x01;
	memory[2] = 0x42;
	memory[3] = 0x01;
	res = get_4bytes(memory, 0);
	assert(res == 133);

	memory[4094] = 0x42;
	memory[4095] = 0x01;
	memory[0] = 0x42;
	memory[1] = 0x01;
	res = get_4bytes(memory, 0);
	assert(res == 133);

	memory[666] = 0x42;
	memory[667] = 0x01;
	memory[668] = 0x42;
	memory[669] = 0x01;
	res = get_4bytes(memory, 666);
	assert(res == 133);
	return (1);
}

int		ld_test(t_vm *vm, t_proccess *proccess);

int		main(void)
{
	t_vm *vm = vm_new(0);
	t_proccess *proccess = proccess_new(0, 1, 0);
	vm_init_memory(vm->memory);

	get_2bytes_test(vm->memory);
	get_4bytes_test(vm->memory);
	return (0);
}
