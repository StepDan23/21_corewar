/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ_name_comment_extend.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:55:16 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 17:40:12 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_current_func_divis(t_asm_data *asm_data, char *line, int i, int j)
{
	if (MACHINE_WAIT_NAME)
	{
		if (j > PROG_NAME_LENGTH)
			ft_error_add(asm_data, ft_strdup("Name too long "), i, 2);
		else
			ft_strncpy(CHAMP_NAME, &line[1], j - 1);
		MACHINE_WAIT_NAME = 0;
		MACHINE_NAME_COMMENT += 1;
	}
	if (MACHINE_WAIT_COMMENT)
	{
		if (j > COMMENT_LENGTH)
			ft_error_add(asm_data, ft_strdup("Comment too long "), i, 2);
		else
			ft_strncpy(CHAMP_COMMENT, &line[1], j - 1);
		MACHINE_WAIT_COMMENT = 0;
		MACHINE_NAME_COMMENT += 2;
	}
}
