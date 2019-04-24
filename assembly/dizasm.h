/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dizasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:27:24 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/24 14:04:37 by lshanaha         ###   ########.fr       */
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
	int			start_row;
	int			bite_of_type;
	int			type_bite_set;
	int			current_count;
	int			arg1_type;
	int			arg2_type;
	int			arg3_type;
	int			arg1_size;
	int			arg2_size;
	int			arg3_size;
}				t_machine;

# define M_HEADER (machine->header)
# define M_NAME (machine->name)
# define M_FIRST_NULL (machine->first_null)
# define M_SIZE (machine->prog_size)
# define M_COMMENT (machine->comment)
# define M_SECOND_NULL (machine->second_null)
# define M_CHAMP_CODE (machine->champ_code)
# define M_START_ROW (machine->start_row)
# define M_TYPE_BITE (machine->bite_of_type)
# define M_TYPE_SET (machine->type_bite_set)
# define M_ARG1 (machine->arg1_type)
# define M_ARG2 (machine->arg2_type)
# define M_ARG3 (machine->arg3_type)
# define M_ARG1_SIZE (machine->arg1_size)
# define M_ARG2_SIZE (machine->arg2_size)
# define M_ARG3_SIZE (machine->arg3_size)

void			ft_solve_comment(t_machine *machine, int bite, int fd_write);
void			ft_solve_size(t_machine *machine, int value, int fd_write);
void			ft_solve_name(t_machine *machine, int bite, int fd_write);
void			ft_solve_header(t_machine *machine, int value, int fd_write);
void			ft_place_arg_value(t_machine *machine, int val, int fd_write,\
int flag);
void			ft_solve_arg3(t_machine *machine, int bite, int fd_write);
void			ft_solve_arg2(t_machine *machine, int bite, int fd_write);
void			ft_solve_arg1(t_machine *machine, int bite, int fd_write);
void			ft_dizasm_name(int fd_write);
void			ft_dizasm_comment(int fd_write);
void			ft_solve_arg_types(t_machine *machine, int bite, int fd_write,\
int command);
void			ft_solve_second_null(t_machine *machine, int bite, int fd);
void			ft_init_machine(t_machine *machine);
int				ft_size_of_arg(t_machine *machine, int arg_type, int command);
void			ft_solve_code(t_machine *machine, int bite, int fd_write);

#endif
