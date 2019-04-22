/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dizasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:27:24 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 21:39:20 by lshanaha         ###   ########.fr       */
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
}				t_machine;

# define M_HEADER (machine->header)
# define M_NAME (machine->name)
# define M_FIRST_NULL (machine->first_null)
# define M_SIZE (machine->prog_size)
# define M_COMMENT (machine->comment)
# define M_SECOND_NULL (machine->second_null)
# define M_CHAMP_CODE (machine->champ_code)
# define M_TEMP (machine->temp)



#endif
