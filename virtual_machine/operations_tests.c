/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:56:09 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/08 02:12:33 by artemiy          ###   ########.fr       */
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
		ft_printf("bit_extracted_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("bit_extracted_test [05] \x1b[31mFAIL\x1b[0m\n");
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
	proccess_init_reg(proccess->registers);
	P_C = 1;
	vm->memory[1] = 0x90; // Байт аргументов 10010000 (DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x10; //00010000
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00000000
	vm->memory[6] = 0x02; // Номер регистра
	//02 90 00 10 00 00 02
	ld(vm, proccess);
	if (P_REG[1] == 1048576 && P_C == 0)
		ft_printf("ld_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
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
	if (P_REG[6] == 255 && P_C == 0)
		ft_printf("ld_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0xFF; //11111111
	vm->memory[3] = 0xFC; //11111101
	vm->memory[4] = 0x07; // Номер регистра
	vm->memory[4092] = 0x00; // 00000000
	vm->memory[4093] = 0x00; // 00000000
	vm->memory[4094] = 0x00; // 00000000
	vm->memory[4095] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [4092] 00 00 00 ff
	ld(vm, proccess);
	if (P_REG[6] == 255 && P_C == 0)
		ft_printf("ld_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [03] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0x02; //00000010
	vm->memory[3] = 0x58; //01011000
	vm->memory[4] = 0x10; // Номер регистра
	vm->memory[88] = 0x00; // 00000000
	vm->memory[89] = 0x00; // 00000000
	vm->memory[90] = 0x00; // 00000000
	vm->memory[91] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [88] 00 00 00 ff
	ld(vm, proccess);
	if (P_REG[15] == 255 && P_C == 0)
		ft_printf("ld_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [04] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(proccess->registers);
	P_C = 0;
	vm->memory[1] = 0x90; // Байт аргументов 10010000 (DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x00; //00000000
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00000000
	vm->memory[6] = 0x02; // Номер регистра
	//02 90 00 10 00 00 02
	ld(vm, proccess);
	if (P_REG[1] == 0 && P_C == 1)
		ft_printf("ld_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ld_test [05] \x1b[31mFAIL\x1b[0m\n");
	
	ft_printf("--------------------------\n");
	return (1);
}

int		lld_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(proccess->registers);
	P_C = 1;
	vm->memory[1] = 0x90; // Байт аргументов 10010000 (DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x10; //00010000
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00000000
	vm->memory[6] = 0x02; // Номер регистра
	//02 90 00 10 00 00 02
	lld(vm, proccess);
	if (P_REG[1] == 1048576 && P_C == 0)
		ft_printf("lld_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
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
	lld(vm, proccess);
	if (P_REG[6] == 255 && P_C == 0)
		ft_printf("lld_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0xFF; //11111111
	vm->memory[3] = 0xFC; //11111101
	vm->memory[4] = 0x07; // Номер регистра
	vm->memory[4092] = 0x00; // 00000000
	vm->memory[4093] = 0x00; // 00000000
	vm->memory[4094] = 0x00; // 00000000
	vm->memory[4095] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [4092] 00 00 00 ff
	lld(vm, proccess);
	if (P_REG[6] == 255 && P_C == 0)
		ft_printf("lld_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [03] \x1b[31mFAIL\x1b[0m\n");
	
	P_C = 1;
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0x02; //00000010
	vm->memory[3] = 0x58; //01011000
	vm->memory[4] = 0x10; // Номер регистра
	vm->memory[600] = 0x00; // 00000000
	vm->memory[601] = 0x00; // 00000000
	vm->memory[602] = 0x00; // 00000000
	vm->memory[603] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [88] 00 00 00 ff
	lld(vm, proccess);
	if (P_REG[15] == 255 && P_C == 0)
		ft_printf("lld_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [04] \x1b[31mFAIL\x1b[0m\n");

	P_C = 1;
	vm->memory[1] = 0xD0; // Байт аргументов 11010000 (IND + REG)
	vm->memory[2] = 0xFD; //11111101
	vm->memory[3] = 0xA8; //10101000
	vm->memory[4] = 0x10; // Номер регистра
	vm->memory[3496] = 0x00; // 00000000
	vm->memory[3497] = 0x00; // 00000000
	vm->memory[3498] = 0x00; // 00000000
	vm->memory[3499] = 0xFF; // 11111111
	//02 D0 01 C7 07
	// [88] 00 00 00 ff
	lld(vm, proccess);
	if (P_REG[15] == 255 && P_C == 0)
		ft_printf("lld_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [05] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(proccess->registers);
	P_C = 0;
	vm->memory[1] = 0x90; // Байт аргументов 10010000 (DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x00; //00000000
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00000000
	vm->memory[6] = 0x02; // Номер регистра
	//02 90 00 10 00 00 02
	lld(vm, proccess);
	if (P_REG[1] == 0 && P_C == 1)
		ft_printf("lld_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lld_test [06] \x1b[31mFAIL\x1b[0m\n");
	
	ft_printf("--------------------------\n");
	return (1);
}

int		st_test(t_vm *vm, t_proccess *proccess)
{
	vm_init_memory(vm->memory);
	proccess_init_reg(P_REG);
	
	P_REG[1] = 42;
	vm->memory[1] = 0x50; // Байт аргументов 10010000 (REG + REG)
	vm->memory[2] = 0x02; //00000010
	vm->memory[3] = 0x03; //00000011
	st(vm, proccess);
	if (P_REG[2] == 42)
		ft_printf("st_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("st_test [01] \x1b[31mFAIL\x1b[0m (%d)\n", P_REG[2]);
	
	P_REG[1] = 707406378;
	vm->memory[1] = 0x70; // Байт аргументов 10010000 (REG + IND)
	vm->memory[2] = 0x02; //00000010
	vm->memory[3] = 0x00; //00000000
	vm->memory[4] = 0x70; //01110000
	st(vm, proccess);
	if (vm->memory[112] == 42 && vm->memory[113] == 42 && vm->memory[114] == 42 &&\
		vm->memory[115] == 42)
		ft_printf("st_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("st_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	P_REG[1] = -252645136;
	P_POS = 100;
	vm->memory[101] = 0x70; // Байт аргументов 10010000 (REG + IND)
	vm->memory[102] = 0x02; //00000010
	vm->memory[103] = 0xFF; //11111111
	vm->memory[104] = 0x9A; //10011010
	st(vm, proccess);
	if (vm->memory[4094] == 240 && vm->memory[4095] == 240 && vm->memory[0] == 240 &&\
		vm->memory[1] == 240)
		ft_printf("st_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("st_test [03] \x1b[31mFAIL\x1b[0m\n");

	P_REG[1] = 1;
	P_POS = 1000;
	vm->memory[1001] = 0x70; // Байт аргументов 10010000 (REG + IND)
	vm->memory[1002] = 0x02; //00000010
	vm->memory[1003] = 0x02; //00000010
	vm->memory[1004] = 0xDA; //11011010
	st(vm, proccess);
	if (vm->memory[1218] == 0 && vm->memory[1219] == 0 && vm->memory[1220] == 0 &&\
		vm->memory[1221] == 1)
		ft_printf("st_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("st_test [04] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		sti_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;

	P_REG[9] = 424242;
	P_REG[10] = 100;
	P_REG[11] = 1;
	vm->memory[1] = 0x54; // Байт аргументов 01010100 (REG + REG + REG)
	vm->memory[2] = 0x0A; //00001010
	vm->memory[3] = 0x0B; //00001011
	vm->memory[4] = 0x0C; //00001100
	sti(vm, proccess);
	if (vm->memory[101] == 0 && vm->memory[102] == 6 && vm->memory[103] == 121 &&\
		vm->memory[104] == 50)
		ft_printf("sti_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	P_POS = 1000;
	P_REG[9] = 424242;
	P_REG[14] = 100;
	vm->memory[1001] = 0x58; // Байт аргументов 01010100 (REG + REG + DIR)
	vm->memory[1002] = 0x0A; //00001010
	vm->memory[1003] = 0x0F; //00001111
	vm->memory[1004] = 0x00; //00000000
	vm->memory[1005] = 0x64; //01100100
	sti(vm, proccess);
	if (vm->memory[1200] == 0 && vm->memory[1201] == 6 && vm->memory[1202] == 121 &&\
		vm->memory[1203] == 50)
		ft_printf("sti_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [02] \x1b[31mFAIL\x1b[0m\n");
	
	P_POS = 2000;
	P_REG[9] = 424242;
	vm->memory[2001] = 0x68; // Байт аргументов 01101000 (REG + DIR + DIR)
	vm->memory[2002] = 0x0A; //00000010
	vm->memory[2003] = 0x00; //00000000
	vm->memory[2004] = 0x64; //01100100
	vm->memory[2005] = 0x00; //00000000
	vm->memory[2006] = 0x64; //01100100
	sti(vm, proccess);
	if (vm->memory[2200] == 0 && vm->memory[2201] == 6 && vm->memory[2202] == 121 &&\
		vm->memory[2203] == 50)
		ft_printf("sti_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [03] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 10;
	P_REG[1] = 424242;
	P_REG[2] = -(4096 * 15);
	P_REG[3] = -12;
	vm->memory[11] = 0x54; // Байт аргументов 01010100 (REG + REG + REG)
	vm->memory[12] = 0x02; //00000010
	vm->memory[13] = 0x03; //00000011
	vm->memory[14] = 0x04; //00000100
	sti(vm, proccess);
	if (vm->memory[4094] == 0 && vm->memory[4095] == 6 && vm->memory[0] == 121 &&\
		vm->memory[1] == 50)
		ft_printf("sti_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [04] \x1b[31mFAIL\x1b[0m\n");
	// vm_dump_memory(vm->memory);
	ft_printf("--------------------------\n");
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
	lld_test(vm, proccess);
	st_test(vm, proccess);
	sti_test(vm, proccess);
	return (0);
}
