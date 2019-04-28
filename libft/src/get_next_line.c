/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 12:49:48 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/25 18:57:55 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include "libft.h"

static t_list	*ft_search(t_list *root, int fd)
{
	t_list				*start;
	t_gnl				*about;

	if ((start = root) == NULL)
		return (0);
	while (root && root->content)
	{
		if (((t_gnl *)(root->content))->fd == fd)
			return (root);
		root = root->next;
	}
	if (!root)
	{
		root = ft_lstnew(NULL, 0);
		ft_lstadd_last(start, root);
	}
	if (!(root->content))
	{
		if (!(about = malloc(sizeof(t_gnl))))
			return (0);
		about->fd = fd;
		about->data = NULL;
		root->content = (void *)about;
	}
	return (root);
}

static int		ft_result(char **line, t_list *root, int i, int j)
{
	char				*temp;

	if (!((t_gnl *)(root->content))->data)
		return (0);
	while (((t_gnl *)(root->content))->data[++i] != '\n' &&\
	((t_gnl *)(root->content))->data[i])
		;
	*line = ft_strnew(i);
	while (++j < i)
		(*line)[j] = ((t_gnl *)(root->content))->data[j];
	(*line)[j] = '\0';
	if (!(((t_gnl *)(root->content))->data[0]))
		return (0);
	temp = ft_strdup(&(((t_gnl *)(root->content))->data[++i]));
	free((((t_gnl *)(root->content))->data));
	((t_gnl *)(root->content))->data = temp;
	if (i > 0)
		return (1);
	else
		return (0);
}

static int		ft_worker(const int fd, char **line, t_list *root, char *str)
{
	char				*temp;
	int					num;

	while ((num = read(fd, str, BUFF_SIZE)) > 0)
	{
		if (!(((t_gnl *)(root->content))->data))
			if (!(((t_gnl *)(root->content))->data = ft_strnew(1)))
				return (-1);
		str[num] = '\0';
		temp = ft_strdup(((t_gnl *)(root->content))->data);
		free(((t_gnl *)(root->content))->data);
		((t_gnl *)(root->content))->data = ft_strjoin_orig(temp, str);
		free(temp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(str);
	if (num == -1)
		return (-1);
	return (ft_result(line, root, -1, -1));
}

int				get_next_line(const int fd, char **line)
{
	static t_list		*root;
	t_list				*temp;
	char				*str;
	int					flag;

	if (fd < 0 || !line)
		return (-1);
	(!root) ? (root = ft_lstnew(NULL, 0)) : (root);
	temp = root;
	if (!(temp = ft_search(root, fd)))
		return (-1);
	if (((t_gnl *)(temp->content))->data)
		if (ft_strchr(((t_gnl *)(temp->content))->data, '\n'))
			return (ft_result(line, temp, -1, -1));
	if (!(str = ft_strnew(BUFF_SIZE)))
		return (-1);
	flag = ft_worker(fd, line, temp, str);
	if (flag <= 0 && root)
	{
		free(((t_gnl *)(root->content))->data);
		free(root->content);
		free(root);
		root = NULL;
	}
	return (flag);
}
