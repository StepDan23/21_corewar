/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type_of_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:15:47 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 18:15:48 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int		ft_get_type_of_file(char *file_name, char *needle)
{
	int		i;
	int		j;
	char	*file_type;

	if (!file_name || !needle)
		return (0);
	i = 0;
	j = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.')
			j = i;
		i++;
	}
	file_type = ft_strdup(&(file_name[j + 1]));
	if (!ft_strcmp(file_type, needle))
		j = 0;
	else
		j = 1;
	(i > 0) ? free(file_type) : 0;
	return (j);
}
