/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:14:39 by fkuhn             #+#    #+#             */
/*   Updated: 2019/03/31 17:02:14 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
/*
**	Структура t_proccess представляет собой процесс 'каретку'
**
**	position - позиция каретки в памяти машины.
**	carry - флаг, показывающий успешно ли выполнилась предыдущая операция
**	этот флаг влияет на выполнение zjmp (выполнится если carry=1).
**	player_id - номер игрока, который создал этот процесс.
**	registers - регистры процесса.
**	is_live - флаг, обозначающий жив ли процесс.
**	command_type - тип комманды, которую надо выполнить.
**	cycles_to_wait - кол-во циклов, которые каретке осталось ждать
**	до выполнения операции.
*/

typedef struct		s_proccess
{
	int				position;
	int				carry;
	int				player_id;
	unsigned int	registers[REG_NUMBER];
	int				is_live;
	int				command_type;
	int				cycles_to_wait;
}					t_proccess;

/*
**	champion
*/
typedef struct		s_champion
{
	char			*name;
	char			*comment;
	unsigned int	size;
	unsigned int	*code;
	unsigned int	id;
}					t_champion;

/*
**	Декларации опкодов операций
*/

# define LIVE		1;
# define LD			2;
# define ST			3;
# define ADD		4;
# define SUB		5;
# define AND		6;
# define OR			7;
# define XOR		8;
# define ZJMP		9;
# define LDI		10;
# define STI		11;
# define FORK		12;
# define LLD		13;
# define LLDI		14;
# define LFORK		15;
# define AFF		16;

#endif
