#include "vm.h"
#include <stdlib.h>
#include "libft.h"

void		champions_add(char *filename, int num, t_champion **head, t_champion **tmp)
{
	t_champion	*champion;

	champion = (t_champion *)malloc(sizeof(t_champion));
	if (!champion)
	{
		ft_printf("Malloc champion error! Exit.");
		exit(2);
	}
	champion->filename = filename;
	champion->id = num;
	champion->code = NULL;
	champion->next = NULL;
	champion->size = 0;

	if (*head == NULL)
	{
		*head = champion;
		*tmp = *head;
		return ;
	}
	(*tmp)->next = champion;
	*tmp = (*tmp)->next;
}
