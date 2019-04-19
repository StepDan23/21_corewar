/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:49:53 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 19:36:35 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		g_temp = 0;

char	*ft_code_create(t_asm_data *asm_data)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str1 = ft_strnew(100000);
	str1 = ft_add_magic_header(str1, &i);
	str1 = ft_add_name(asm_data, str1, &i, -1);
	str1 = ft_add_null(str1, &i);
	ft_printf("str = %s, i = %d\n", str1, i);
	g_temp = i;
	i = 0;
	str2 = ft_strnew(100000);
	str2 = ft_add_comment(asm_data, str1, &i, -1);
	str2 = ft_add_null(str2, &i);
	ft_printf("str2 = %s, i = %d\n", str1, i);

	return (str1);
}

void	ft_convert_to_binary(t_asm_data *asm_data, char *name)
{
	int		fd;
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	while (name[i] != '.')
		i++;
	temp = ft_strsub(name, 0, i);
	str = ft_strjoin_orig(temp, ".cor");
	fd = open(str, O_CREAT, O_APPEND, S_IWRITE | S_IREAD);
	free(str);
	str = ft_code_create(asm_data);
	free(temp);
	close(fd);
}
