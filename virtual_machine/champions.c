#include "vm.h"
#include <stdlib.h>
#include "libft.h"

void		champions_add(char *filename, int num, t_champion **head)
{
	t_champion	*new_champ;

	new_champ = (t_champion *)malloc(sizeof(t_champion));
	if (!new_champ)
	{
		ft_printf("Malloc champion error! Exit.");
		exit(2);
	}
	new_champ->filename = filename;
	new_champ->id = num;
	new_champ->code = NULL;
	new_champ->next = NULL;
	new_champ->size = 0;

	if (*head == NULL)
	{
		*head = new_champ;
		return ;
	}
	new_champ->next = *head;
	*head = new_champ;
}
