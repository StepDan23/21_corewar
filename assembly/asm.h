
#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"
/*
char	commands[16][6] = {
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};
*/
/*
** как обработать эти марки?
*/

typedef struct	s_marks
{
	char		*name;
	int			count_number_in_data;
}				t_marks;

typedef struct	s_token
{
	char		*token;
	int			num_string;
	int			num_clomun;
	int			error;
}				t_token;

/*
** if flag == 0, then no name and comment found. if flag == 1, then no comment.
*/
typedef struct	s_champ_data
{
	t_token		*name;
	t_token		*comment;
	int			flag;
	int			open_brackets;
	int			close_brackets;
}				t_champ_data;

typedef struct	s_lex_str
{
	int			num;
	t_token		*command;
	t_token		*arg_1;
	char		delimetr1;
	t_token		*arg_2;
	char		delimetr2;
	t_token		*arg_3;
	int			new_line;
}				t_lex_str;

/*
** основная структура содержит:
** структуру для записи имени и комментария чемпиона
** связанный список для хранения меток
** корень дерева для записи и хранения токенов лексического анализа
** связанный список для записи встреченных ошибок
*/
typedef struct		s_asm
{
	t_champ_data	*champ_data;
	t_list			*marks;
	t_rbroot		*lex_tree;
	t_list			*errors;
	// ! может этот флаг и не нужен будет
	int				error_flag;
	int				status_flag;
}					t_asm;

t_lex_str		*ft_lex_str_init();
t_token			*ft_token_init();
t_marks			*ft_marks_init();
t_asm			*ft_asm_init();

# define CHAMP_DATA (asm_data->champ_data)
# define MARKS (asm_data->marks)
# define LEX_TREE (asm_data->lex_tree)
# define ERRORS (asm_data->errors)
# define ERROR_FLAG (asm_data->error_flag)
# define STATUS_FLAG (asm_data->status_flag)

# define WAIT_NAME 1
# define WAIT_COMMENT 2

#endif
