#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "libft.h"
#include "vm.h"

int main(int ac, char **av)
{
	printf("\n%s\n", "TEST check_filename");
	assert(check_filename(".cor") == 0);
		printf("1) %s :			ok\n", ".cor");
	assert(check_filename("1.cor") == 1);
		printf("2) %s :			ok\n", "1.cor");
	assert(check_filename(".cor.cor") == 1);
		printf("3) %s :			ok\n", ".cor.cor");
	assert(check_filename("champ.cor") == 1);
		printf("4) %s :			ok\n", "champ.cor");
	assert(check_filename("champ.core") == 0);
		printf("5) %s :			ok\n", "champ.core");
	
	t_vm *vm = vm_new();
	args_read(ac, av, vm);
	
	printf("\nchampions number:\t\t%d\n\n", vm->champion_count);
	if (vm->champion[0])
		printf("filename:\t%s\nid:\t\t%d\n\n", vm->champion[0]->filename, vm->champion[0]->id);
	else
	{
		printf("no champ with id\t%d\n\n", 1);
	}
	if (vm->champion[1])
		printf("filename:\t%s\nid:\t\t%d\n\n", vm->champion[1]->filename, vm->champion[1]->id);
	else
	{
		printf("no champ with id\t%d\n\n", 2);
	}
	if (vm->champion[2])
		printf("filename:\t%s\nid:\t\t%d\n\n", vm->champion[2]->filename, vm->champion[2]->id);
	else
	{
		printf("no champ with id\t%d\n\n", 3);
	}
	if (vm->champion[3])
		printf("filename:\t%s\nid:\t\t%d\n\n", vm->champion[3]->filename, vm->champion[3]->id);
	else
	{
		printf("no champ with id\t%d\n\n", 4);
	}
	
	// t_vm *vm = vm_new();
	// t_champion *x;
	// int xx = check_args(ac, av, vm);
	// printf("return check_args: %d\ndump: %d\n", xx, vm->dump);
	// printf("cycles_dump: %d\n", vm->cycles_to_dump);
	// while (vm->champion)
	// {
	// 	printf("id:\t%d\nfile:\t%s\n------------\n", vm->champion->id, vm->champion->filename);
	// 	x = vm->champion->next;
	// 	champion_free(vm->champion);
	// 	vm->champion = x;
	// }
	// free(vm);
//	int x = champion_count(ac, av);
//	printf("x: %d\n", x);
	return (0);
}

