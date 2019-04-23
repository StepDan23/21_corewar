/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dizasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:27:24 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/23 10:20:35 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIZASM_H
# define DIZASM_H

# include "libft.h"
# include "../op.h"

typedef struct	s_machine
{
	int			header;
	int			name;
	int			first_null;
	int			prog_size;
	int			comment;
	int			second_null;
	int			champ_code;
	int			temp;
	int			current_count;
}				t_machine;

# define M_HEADER (machine->header)
# define M_NAME (machine->name)
# define M_FIRST_NULL (machine->first_null)
# define M_SIZE (machine->prog_size)
# define M_COMMENT (machine->comment)
# define M_SECOND_NULL (machine->second_null)
# define M_CHAMP_CODE (machine->champ_code)
# define M_TEMP (machine->temp)
# define M_COUNT (machine->current_count)



#endif
