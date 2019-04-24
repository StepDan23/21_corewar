/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compile_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:36:25 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 20:17:33 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*ft_str_realloc(char *str, int i)
{
	char	*temp;

	if (i == 0)
		return (str);
	temp = (char *)realloc(str, ((i / 100000) * 100000 + 100000));
	free(str);
	return (temp);
}
