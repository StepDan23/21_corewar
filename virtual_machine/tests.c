#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "libft.h"
#include "vm.h"

int main(void)
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
	
	printf("\n%s\n", "TEST champions_add");
	t_champion *test = NULL;
	t_champion *tmp_test = NULL;
	champions_add("test.cor", 1, &test, &tmp_test);
	assert(test->id == 1 && tmp_test->id == 1 && ft_strequ(test->filename, "test.cor") &&
			ft_strequ(tmp_test->filename, "test.cor"));
		printf("1) head and tmp first add good\n");
	champions_add("test2.cor", 2, &test, &tmp_test);
	assert(test->id == 1 && tmp_test->id == 2 && ft_strequ(test->filename, "test.cor") &&
			ft_strequ(tmp_test->filename, "test2.cor"));
		printf("2) head the same and tmp new add good\n");
		free(test);
		free(tmp_test);
	return (0);
}

