/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:56:09 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/07 21:11:32 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tests.h"
#include <assert.h>

int		bit_extracted_test(void)
{
	if (bit_extracted(144, 2, 7) == 2)
		ft_printf("bit_extracted_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	if (bit_extracted(144, 2, 5) == 1)
		ft_printf("bit_extracted_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	if (bit_extracted(244, 2, 7) == 3)
		ft_printf("bit_extracted_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [03] \x1b[31mFAIL\x1b[0m\n");
	
	if (bit_extracted(244, 2, 5) == 3)
		ft_printf("bit_extracted_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [04] \x1b[31mFAIL\x1b[0m\n");
	
	if (bit_extracted(244, 2, 3) == 1)
		ft_printf("bit_extracted_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [04] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		get_2bytes_test(unsigned char *memory)
{
	int	res;

	memory[0] = 0x42;
	memory[1] = 0x01;
	res = get_2bytes(memory, 0);
	if (res == 16897)
		ft_printf("get_2bytes_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_2bytes_test [01] \x1b[31mFAIL\x1b[0m\n");

	memory[0] = 0x01;
	memory[4095] = 0x42;
	res = get_2bytes(memory, 4095);
	if (res == 16897)
		ft_printf("get_2bytes_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_2bytes_test [02] \x1b[31mFAIL\x1b[0m\n");

	memory[44] = 0xFF;
	memory[45] = 0xFF;
	res = get_2bytes(memory, 44);
	if (res == -1)
		ft_printf("get_2bytes_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_2bytes_test [03] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		get_4bytes_test(unsigned char *memory)
{
	int	res;

	memory[0] = 0x00;
	memory[1] = 0x00;
	memory[2] = 0x00;
	memory[3] = 0x01;
	res = get_4bytes(memory, 0);
	if (res == 1)
		ft_printf("get_4bytes_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_4bytes_test [01] \x1b[31mFAIL\x1b[0m\n");

	memory[0] = 0x00; //00000000
	memory[1] = 0x00; //00000000
	memory[2] = 0x10; //00010000
	memory[3] = 0x00; //00000000
	res = get_4bytes(memory, 0);
	if (res == 4096)
		ft_printf("get_4bytes_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_4bytes_test [02] \x1b[31mFAIL\x1b[0m\n");

	memory[4094] = 0x42; //01000010
	memory[4095] = 0x01; //00000001
	memory[0] = 0x42; //   01000010
	memory[1] = 0x01; //   00000001
	res = get_4bytes(memory, 4094);
	if (res == 1107378689)
		ft_printf("get_4bytes_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_4bytes_test [03] \x1b[31mFAIL\x1b[0m\n");

	memory[666] = 0xFF;
	memory[667] = 0xFF;
	memory[668] = 0xFF;
	memory[669] = 0xFF;
	res = get_4bytes(memory, 666);
	// ft_printf("%d\n", res);
	if (res == -1)
		ft_printf("get_4bytes_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("get_4bytes_test [04] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		ld_test(t_vm *vm, t_proccess *proccess)
{
	vm->memory[1] = 0x90; // Байт аргументов 10010000 (DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x10; //00010000
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00000000
	vm->memory[6] = 0x02; // Номер регистра
	//02 90 00 10 00 00 02
	ld(vm, proccess);
	if (P_REG[1] == 1048576)
		ft_printf("ld_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0x01; //00000001
	vm->memory[3] = 0xC7; //11000111
	vm->memory[4] = 0x07; // Номер регистра
	vm->memory[455] = 0x00; // 00000000
	vm->memory[456] = 0x00; // 00000000
	vm->memory[457] = 0x00; // 00000000
	vm->memory[458] = 0xff; // 11111111
	//02 D0 01 C7 07
	// [455] 00 00 00 ff
	ld(vm, proccess);
	if (P_REG[6] == 255)
		ft_printf("ld_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0xFF; //11111111
	vm->memory[3] = 0xFC; //11111101
	vm->memory[4] = 0x07; // Номер регистра
	vm->memory[4092] = 0x00; // 00000000
	vm->memory[4093] = 0x00; // 00000000
	vm->memory[4094] = 0x00; // 00000000
	vm->memory[4095] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [455] 00 00 00 ff
	ld(vm, proccess);
	if (P_REG[6] == 255)
		ft_printf("ld_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [03] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	ft_printf("%d\n", P_REG[6]);
	return (1);
}

int		main(void)
{
	t_vm *vm = vm_new(0);
	t_proccess *proccess = proccess_new(0, 1, 0);
	proccess_add(&vm->process, proccess);
	vm_init_memory(vm->memory);

	bit_extracted_test();
	get_2bytes_test(vm->memory);
	get_4bytes_test(vm->memory);
	ld_test(vm, proccess);
	return (0);
}
