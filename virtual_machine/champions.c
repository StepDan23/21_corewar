#include "vm.h"
#include <stdlib.h>

t_champion	*new_champ(int number, char *filename)
{
	t_champion	*champion;

	champion = (t_champion *)malloc(sizeof(t_champion));
	if (!champion)
		return (NULL);
	champion->filename = filename;
	champion->id = number;
	champion->code = NULL;
	champion->next = NULL;
	champion->size = 0;
	return (champion);
}
