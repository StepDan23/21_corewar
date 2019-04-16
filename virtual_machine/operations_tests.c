/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:56:09 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/16 16:33:41 by fkuhn            ###   ########.fr       */
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
	vm->memory[1001] = 0x58; // Байт аргументов 01011000 (REG + REG + DIR)
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
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 100;
	P_REG[1] = 424242;
	vm->memory[101] = 0x78; // Байт аргументов 01111000 (REG + IND + DIR)
	vm->memory[102] = 0x02; //00000010 (reg[1] = 424242)
	vm->memory[103] = 0x00; //00000000
	vm->memory[104] = 0x64; //01100100 (100)
	vm->memory[105] = 0x00; //00000000
	vm->memory[106] = 0x64; //01100100 (100)
	vm->memory[200] = 0x00; //00000000
	vm->memory[201] = 0x00; //00000000
	vm->memory[202] = 0x00; //00000000
	vm->memory[203] = 0x0a; //00001010 (10)
	sti(vm, proccess);
	if (vm->memory[210] == 0 && vm->memory[211] == 6 && vm->memory[212] == 121 &&\
		vm->memory[213] == 50)
		ft_printf("sti_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [05] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 10;
	P_REG[1] = 424242;
	P_REG[2] = 1233141;
	vm->memory[11] = 0x64; // Байт аргументов 01010100 (REG + DIR + REG)
	vm->memory[12] = 0x02; //00000010
	vm->memory[13] = 0xFF; //11111111
	vm->memory[14] = 0x9C; //10011100 (-100)
	vm->memory[15] = 0x03; //00000011 ((-100) + 1233141) % IDX_MOD = 504
	sti(vm, proccess);
	if (vm->memory[155] == 0 && vm->memory[156] == 6 && vm->memory[157] == 121 &&\
		vm->memory[158] == 50)
		ft_printf("sti_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("sti_test [06] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		lldi_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);

	P_POS = 0;
	P_REG[9] = 10;
	P_REG[10] = 10;
	vm->memory[1] = 0x54; // Байт аргументов 01010100 (REG + REG + REG)
	vm->memory[2] = 0x0A; //00001010
	vm->memory[3] = 0x0B; //00001011
	vm->memory[4] = 0x0C; //00001100
	vm->memory[20] = 0x0C; //00001100
	vm->memory[21] = 0x0C; //00001100
	vm->memory[22] = 0x0C; //00001100
	vm->memory[23] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[11] == 202116108)
		ft_printf("lldi_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 10;
	vm->memory[1] = 0x64; // Байт аргументов 01100100 (REG + DIR + REG)
	vm->memory[2] = 0x02; //00001010
	vm->memory[3] = 0x0B; //00001011
	vm->memory[4] = 0x0C; //00001100
	vm->memory[5] = 0x10; //00001100
	vm->memory[2838] = 0x0C; //00001100
	vm->memory[2839] = 0x0C; //00001100
	vm->memory[2840] = 0x0C; //00001100
	vm->memory[2841] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("lldi_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [02] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 10;
	vm->memory[1] = 0x94; // Байт аргументов 01100100 (DIR + REG + REG)
	vm->memory[2] = 0x0B; //00001011
	vm->memory[3] = 0x0C; //00001100
	vm->memory[4] = 0x02; //00001010
	vm->memory[5] = 0x10; //00001100
	vm->memory[2838] = 0x0C; //00001100
	vm->memory[2839] = 0x0C; //00001100
	vm->memory[2840] = 0x0C; //00001100
	vm->memory[2841] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("lldi_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [03] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xA4; // Байт аргументов 01100100 (DIR + DIR + REG)
	vm->memory[2] = 0x0B; //00001011
	vm->memory[3] = 0x0C; //00001100
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x0A; //00001010
	vm->memory[6] = 0x10; //00010000
	vm->memory[2838] = 0x0C; //00001100
	vm->memory[2839] = 0x0C; //00001100
	vm->memory[2840] = 0x0C; //00001100
	vm->memory[2841] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("lldi_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [04] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xE4; // Байт аргументов 01100100 (IND + DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x0A; //00001010
	vm->memory[4] = 0x0B; //00001011
	vm->memory[5] = 0x0C; //00001100
	vm->memory[6] = 0x10; //00010000
	vm->memory[10] = 0x00;//00000000
	vm->memory[11] = 0x00;//00000000
	vm->memory[12] = 0x00;//00000000
	vm->memory[13] = 0x0A;//00001010
	vm->memory[2838] = 0x0C; //00001100
	vm->memory[2839] = 0x0C; //00001100
	vm->memory[2840] = 0x0C; //00001100
	vm->memory[2841] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("lldi_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [05] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xE4; // Байт аргументов 01100100 (IND + DIR + REG)
	vm->memory[2] = 0xFF; //00001011
	vm->memory[3] = 0x01; //00001100
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00001010 (0)
	vm->memory[6] = 0x10; //00010000
	vm->memory[3841] = 0x7F;//01111111
	vm->memory[3842] = 0xFF;//11111111
	vm->memory[3843] = 0xFF;//11111111
	vm->memory[3844] = 0xD0;//11010000 (2147483600)
	vm->memory[4048] = 0x0C; //00001100
	vm->memory[4049] = 0x0C; //00001100
	vm->memory[4050] = 0x0C; //00001100
	vm->memory[4051] = 0x0C; //00001100
	lldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("lldi_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("lldi_test [06] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	// vm_dump_memory(vm->memory);
	return (1);
}


int		ldi_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);

	P_POS = 0;
	P_REG[9] = 10;
	P_REG[10] = 10;
	vm->memory[1] = 0x54; // Байт аргументов 01010100 (REG + REG + REG)
	vm->memory[2] = 0x0A; //00001010
	vm->memory[3] = 0x0B; //00001011
	vm->memory[4] = 0x0C; //00001100
	vm->memory[20] = 0x0C; //00001100
	vm->memory[21] = 0x0C; //00001100
	vm->memory[22] = 0x0C; //00001100
	vm->memory[23] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[11] == 202116108)
		ft_printf("ldi_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [01] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 10;
	vm->memory[1] = 0x64; // Байт аргументов 01100100 (REG + DIR + REG)
	vm->memory[2] = 0x02; //00001010
	vm->memory[3] = 0x0B; //00001011
	vm->memory[4] = 0x0C; //00001100
	vm->memory[5] = 0x10; //00001100
	vm->memory[2838 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2839 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2840 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2841 % IDX_MOD] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("ldi_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [02] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 10;
	vm->memory[1] = 0x94; // Байт аргументов 01100100 (DIR + REG + REG)
	vm->memory[2] = 0x0B; //00001011
	vm->memory[3] = 0x0C; //00001100
	vm->memory[4] = 0x02; //00001010
	vm->memory[5] = 0x10; //00001100
	vm->memory[2838 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2839 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2840 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2841 % IDX_MOD] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("ldi_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [03] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xA4; // Байт аргументов 01100100 (DIR + DIR + REG)
	vm->memory[2] = 0x0B; //00001011
	vm->memory[3] = 0x0C; //00001100
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x0A; //00001010
	vm->memory[6] = 0x10; //00010000
	vm->memory[2838 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2839 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2840 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2841 % IDX_MOD] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("ldi_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [04] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xE4; // Байт аргументов 01100100 (IND + DIR + REG)
	vm->memory[2] = 0x00; //00000000
	vm->memory[3] = 0x0A; //00001010
	vm->memory[4] = 0x0B; //00001011
	vm->memory[5] = 0x0C; //00001100
	vm->memory[6] = 0x10; //00010000
	vm->memory[10] = 0x00;//00000000
	vm->memory[11] = 0x00;//00000000
	vm->memory[12] = 0x00;//00000000
	vm->memory[13] = 0x0A;//00001010
	vm->memory[2838 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2839 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2840 % IDX_MOD] = 0x0C; //00001100
	vm->memory[2841 % IDX_MOD] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("ldi_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [05] \x1b[31mFAIL\x1b[0m\n");
	
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xE4; // Байт аргументов 01100100 (IND + DIR + REG)
	vm->memory[2] = 0xFF; //00001011
	vm->memory[3] = 0x01; //00001100
	vm->memory[4] = 0x00; //00000000
	vm->memory[5] = 0x00; //00001010 (0)
	vm->memory[6] = 0x10; //00010000
	vm->memory[3841] = 0x7F;//01111111
	vm->memory[3842] = 0xFF;//11111111
	vm->memory[3843] = 0xFF;//11111111
	vm->memory[3844] = 0xFF;//11111111 (2147483647)
	vm->memory[511] = 0x0C; //00001100
	vm->memory[512] = 0x0C; //00001100
	vm->memory[513] = 0x0C; //00001100
	vm->memory[514] = 0x0C; //00001100
	ldi(vm, proccess);
	if (P_REG[15] == 202116108)
		ft_printf("ldi_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("ldi_test [06] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	// vm_dump_memory(vm->memory);
	return (1);
}

int		logic_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);

	P_POS = 0;
	P_REG[1] = 0;
	P_REG[2] = 0;
	vm->memory[1] = 0x54; // Байт аргументов 01010100 (REG + REG + REG)
	vm->memory[2] = 0x02; //00001010
	vm->memory[3] = 0x03; //00001011
	vm->memory[4] = 0x04; //00001100
	and(vm, proccess);
	if (P_REG[3] == 0 && P_C == 1)
		ft_printf("and_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [01] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[3] == 0 && P_C == 1)
		ft_printf("or_test  [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [01] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[3] == 0 && P_C == 1)
		ft_printf("xor_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [01] \x1b[31mFAIL\x1b[0m\n");
	P_REG[1] = 1;
	P_REG[2] = 3;
	and(vm, proccess);
	if (P_REG[3] == 1 && P_C == 0)
		ft_printf("and_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [02] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[3] == 3 && P_C == 0)
		ft_printf("or_test  [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [02] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[3] == 2 && P_C == 0)
		ft_printf("xor_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [02] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 0;
	vm->memory[1] = 0x64; // Байт аргументов 01100100 (REG + DIR + REG)
	vm->memory[2] = 0x02;
	vm->memory[3] = 0x00;
	vm->memory[4] = 0x00;
	vm->memory[5] = 0x00;
	vm->memory[6] = 0x01;
	vm->memory[7] = 0x05;
	and(vm, proccess);
	if (P_REG[4] == 0 && P_C == 1)
		ft_printf("and_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [03] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[4] == 1 && P_C == 0)
		ft_printf("or_test  [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [03] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[4] == 1 && P_C == 0)
		ft_printf("xor_test [03] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [03] \x1b[31mFAIL\x1b[0m\n");
	P_REG[1] = 3;
	and(vm, proccess);
	if (P_REG[4] == 1 && P_C == 0)
		ft_printf("and_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [04] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[4] == 3 && P_C == 0)
		ft_printf("or_test  [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [04] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 0;
	vm->memory[1] = 0xA4; // Байт аргументов 10100100 (DIR + DIR + REG)
	vm->memory[2] = 0x00;
	vm->memory[3] = 0x00;
	vm->memory[4] = 0x00;
	vm->memory[5] = 0x01;
	vm->memory[6] = 0x00;
	vm->memory[7] = 0x00;
	vm->memory[8] = 0x00;
	vm->memory[9] = 0x02;
	vm->memory[10] = 0x02;
	and(vm, proccess);
	if (P_REG[4] == 0 && P_C == 1)
		ft_printf("and_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [05] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[1] == 3 && P_C == 0)
		ft_printf("or_test  [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [05] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[1] == 3 && P_C == 0)
		ft_printf("xor_test [04] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [04] \x1b[31mFAIL\x1b[0m\n");
	vm->memory[2] = 0x00;
	vm->memory[3] = 0x00;
	vm->memory[4] = 0x00;
	vm->memory[5] = 0x03;
	vm->memory[6] = 0x00;
	vm->memory[7] = 0x00;
	vm->memory[8] = 0x00;
	vm->memory[9] = 0x02;
	and(vm, proccess);
	if (P_REG[1] == 2 && P_C == 0)
		ft_printf("and_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [06] \x1b[31mFAIL\x1b[0m\n");

	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	P_REG[1] = 0;
	vm->memory[1] = 0x74; // Байт аргументов 01110100 (REG + IND + REG)
	vm->memory[2] = 0x02;
	vm->memory[3] = 0x03;
	vm->memory[4] = 0xE8; //(1000)
	vm->memory[5] = 0x03;
	vm->memory[488] = 0x00;
	vm->memory[489] = 0x00;
	vm->memory[490] = 0x00;
	vm->memory[491] = 0x01;
	and(vm, proccess);
	if (P_REG[2] == 0 && P_C == 1)
		ft_printf("and_test [07] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [07] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[2] == 1 && P_C == 0)
		ft_printf("or_test  [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [06] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[2] == 1 && P_C == 0)
		ft_printf("xor_test [05] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [05] \x1b[31mFAIL\x1b[0m\n");
	P_REG[1] = 17385;
	vm->memory[488] = 0x00;
	vm->memory[489] = 0x99;
	vm->memory[490] = 0x15;
	vm->memory[491] = 0x05;
	and(vm, proccess);
	if (P_REG[2] && P_C == 0)
		ft_printf("and_test [08] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [08] \x1b[31mFAIL\x1b[0m\n");
	// Байт аргументов 11110100 (IND + IND + REG)
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);
	P_POS = 0;
	vm->memory[1] = 0xF4; // Байт аргументов 11110100 (IND + IND + REG)
	vm->memory[2] = 0x03;
	vm->memory[3] = 0xE8; //(1000)
	vm->memory[4] = 0xFC; //11111100
	vm->memory[5] = 0x18; //00011000 (-1000)
	vm->memory[6] = 0x03;
	vm->memory[488] = 0x00;
	vm->memory[489] = 0x00;
	vm->memory[490] = 0x00;
	vm->memory[491] = 0x20;
	vm->memory[3608] = 0x00;
	vm->memory[3609] = 0x00;
	vm->memory[3610] = 0x00;
	vm->memory[3611] = 0x01;
	// vm_dump_memory(vm->memory);
	and(vm, proccess);
	if (P_REG[2] == 0 && P_C == 1)
		ft_printf("and_test [09] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [09] \x1b[31mFAIL\x1b[0m\n");
	or(vm, proccess);
	if (P_REG[2] == 33 && P_C == 0)
		ft_printf("or_test  [07] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("or_test  [07] \x1b[31mFAIL\x1b[0m\n");
	xor(vm, proccess);
	if (P_REG[2] == 33 && P_C == 0)
		ft_printf("xor_test [06] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("xor_test [06] \x1b[31mFAIL\x1b[0m\n");
	vm->memory[491] = 0x21;
	and(vm, proccess);
	if (P_REG[2] == 1 && P_C == 0)
		ft_printf("and_test [10] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("and_test [10] \x1b[31mFAIL\x1b[0m\n");
	// Байт аргументов 10110100 (DIR + IND + REG)
	ft_printf("--------------------------\n");
	return (1);
}

int		zjmp_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);

	P_POS = 100;
	P_C = 1;
	vm->memory[101] = 0x01;
	vm->memory[102] = 0xF4;
	zjmp(vm, proccess);
	if (P_POS == 600)
		ft_printf("zjmp_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("zjmp_test [01] \x1b[31mFAIL\x1b[0m\n");
	P_POS = 100;
	P_C = 0;
	zjmp(vm, proccess);
	if (P_POS == 103)
		ft_printf("zjmp_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("zjmp_test [02] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		fork_test(t_vm *vm, t_proccess *proccess)
{
	proccess_init_reg(P_REG);
	vm_init_memory(vm->memory);

	P_POS = 100;
	vm->memory[101] = 0x01;
	vm->memory[102] = 0xF4;
	P_REG[15] = 89173;
	P_REG[7] = -2786426;
	P_REG[0] = 3;
	ft_fork(vm, proccess);
	if (vm->process->id == proccess->id + 1 && vm->process->position == 600 &&\
		vm->process->registers[0] == P_REG[0] && vm->process->registers[7] == P_REG[7]\
		&& vm->process->registers[15] == P_REG[15])
		ft_printf("fork_test [01] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("fork_test [01] \x1b[31mFAIL\x1b[0m\n");
	P_POS = 100;
	vm->memory[101] = 0xFF;
	vm->memory[102] = 0xFF;
	ft_fork(vm, proccess);
	if (vm->process->id == vm->process->next->id + 1 && vm->process->position == 99 &&\
		vm->process->registers[0] == P_REG[0] && vm->process->registers[7] == P_REG[7]\
		&& vm->process->registers[15] == P_REG[15])
		ft_printf("fork_test [02] \x1b[32mOK\x1b[0m\n");
	else
		ft_printf("fork_test [02] \x1b[31mFAIL\x1b[0m\n");
	ft_printf("--------------------------\n");
	return (1);
}

int		main(void)
{
	t_vm *vm = vm_new();
	t_proccess *proccess = proccess_new(0, 1, 0);
	proccess_add(&vm->process, proccess);
	vm_init_memory(vm->memory);

	ft_printf("Unit tests:\n\n");
	bit_extracted_test();
	get_2bytes_test(vm->memory);
	get_4bytes_test(vm->memory);
	ld_test(vm, proccess);
	lld_test(vm, proccess);
	st_test(vm, proccess);
	sti_test(vm, proccess);
	ldi_test(vm, proccess);
	lldi_test(vm, proccess);
	logic_test(vm, proccess);
	zjmp_test(vm, proccess);
	fork_test(vm, proccess);
	return (0);
}
