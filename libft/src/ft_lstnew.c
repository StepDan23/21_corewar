/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:12:24 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 17:58:42 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_elem;

	if (!(new_elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_elem->content = ft_memalloc(content_size);
	if (new_elem->content == NULL)
	{
		free(new_elem);
		return (0);
	}
	if (content == NULL && content_size == 0)
	{
		free(new_elem->content);
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	else if (content != NULL)
	{
		new_elem->content = ft_memcpy(new_elem->content, content,\
		content_size);
		new_elem->content_size = content_size;
	}
	new_elem->next = NULL;
	return (new_elem);
}
