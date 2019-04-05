/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreutel <ttreutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:14:39 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/05 21:25:43 by ttreutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"

/*
**	Структура t_proccess представляет собой процесс 'каретку'
**
**	position - позиция каретки в памяти машины.
**	carry - этот флаг влияет на выполнение zjmp (выполнится если carry=1).
**	player_id - номер игрока, который создал этот процесс.
**	registers - регистры процесса.
**	is_live - флаг, обозначающий жив ли процесс.
**	command_type - тип комманды, которую надо выполнить.
**	cycles_to_wait - кол-во циклов, которые каретке осталось ждать
**	до выполнения операции.
*/

typedef struct			s_proccess
{
	int					position;
	int					carry;
	int					player_id;
	unsigned int		registers[REG_NUMBER];
	int					is_live;
	int					command_type;
	int					cycles_to_wait;
}						t_proccess;

/*
**	champion
**	name - имя чемпиона
**	comment - комментарий
**	size - размер исполняемого кода
**	code - указатель на начало кода
*/

typedef struct			s_champion
{
	char				*filename;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		size;
	unsigned char		*code;
	unsigned int		id;
	struct s_champion	*next;
}						t_champion;

/*
**	vm Virtual machine
**	cycles - кол-во выполненных циклов
**	cycles_to_die - кол-во оставшихся циклов до проверки процессов на live
**	cycles_to_dump - кол-во циклов до дампа памяти
**	dump - периодичность дампа памяти в циклах
**	cycles_die - периодичность проверки на live в циклах
**	*process - список живых процессов (кареток)
**	*champion - список чемпионов (пока хз с этим)
**	memory - область памяти (зона боевых действий)
*/

typedef struct			vm
{
	unsigned int		cycles;
	unsigned int		cycles_to_die;
	int					cycles_to_dump;
	int					dump;
	unsigned int		cycles_die;
	t_proccess			*process;
	t_champion			*champion;
	unsigned char		memory[MEM_SIZE];

}						t_vm;

/*
**	Декларации опкодов операций
*/

# define LIVE			1
# define LD				2
# define ST				3
# define ADD			4
# define SUB			5
# define AND			6
# define OR				7
# define XOR			8
# define ZJMP			9
# define LDI			10
# define STI			11
# define FORK			12
# define LLD			13
# define LLDI			14
# define LFORK			15
# define AFF			16

/*
**	Error codes
*/

# define MAGIC_ERR		1
# define COMM_ERR		2
# define NAME_ERR		3
# define CODE_ERR		4
# define CODE_LEN_ERR	5

t_champion				*new_champ(int number, char *filename);
void					champion_free(t_champion *hero);

void					read_all_champs(t_champion *champs);
int						read_champ(t_champion *champ);
int						read_4bytes(int fd);
int						read_magic(int fd);
int						check_null(int fd);
int						read_code(int fd, t_champion *champ);
void					print_error_exit(int code);

t_vm					*vm_new(void);
void					vm_spread_champs(unsigned char *memory, t_champion *chapms);
void					vm_dump_memory(unsigned char *memory);

int						is_all_digit(char *str);
int						count_avaliable(t_vm *vm);
int						check_filename(char *file);
int						check_args(int ac, char **av, t_vm *vm);
int						manage_flag(t_vm *vm, char *flag, char *param, int *count);

void					champions_add(char *filename, int num, t_champion **head);
#endif
