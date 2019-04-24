#include "vm.h"
#include <stdlib.h>
#include "libft.h"

void		champions_add(char *filename, int id, t_champion **head)
{
	t_champion	*new_champ;

	new_champ = (t_champion *)malloc(sizeof(t_champion));
	if (!new_champ)
	{
		ft_printf("Malloc champion error! Exit.");
		exit(2);
	}
	new_champ->filename = filename;
	new_champ->id = id;
	new_champ->code = NULL;
	new_champ->size = 0;
	new_champ->last_live = 0;
	new_champ->last_live = 0;
	new_champ->lives_in_period = 0;
	head[id - 1] = new_champ;
}

void		champion_free(t_champion *hero)
{
	if (hero->code)
		free(hero->code);
	free(hero);
}

int			champion_number(t_champion **arr)
{
	t_champion	*hero;
	int			num;
	int			i;

	i = 0;
	num = 1;
	hero = arr[i];
	while (i < MAX_PLAYERS)
	{
		if (hero)
		{
			if (num == hero->id)
				num++;
		}
		hero = arr[++i];
	}
	return (num);
}
