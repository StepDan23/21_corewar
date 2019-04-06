/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:56:09 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/06 16:32:57 by fkuhn            ###   ########.fr       */
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
	ft_printf("%d\n", res);
	assert(res == 133);
	return (1);
}

int		main(void)
{
	unsigned char	memory[4096];
	vm_init_memory(memory);
	ft_printf("%d\n", sizeof(short));
	get_2bytes_test(memory);
	return (0);
}
