
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
** if type of error = 1, than lex error
** if type of error = 2, than syntax error
** if type of error = 3, than semantic error
*/
typedef struct	s_error
{
	char		*str;
	int			num_str;
	int			num_column;
	int			type_of_error;
}				t_error;

/*
** основная структура содержит:
** текущий номер строки в файле
** порядковый номер строки содержащий данные
** структуру для записи имени и комментария чемпиона
** связанный список для хранения меток
** корень дерева для записи и хранения токенов лексического анализа
** связанный список для записи встреченных ошибок
** Если current_state = 0, то система в режиме ожидания
** Если current_state = 1 или 2, то режим принятия имени/коммента.
** Если current_state > 3, то принятие имени/коммента закончено. Система ждет
** иных параметров.
**
*/
typedef struct		s_asm
{
	int				string_with_data;
	int				string_current;
	t_champ_data	*champ_data;
	t_list			*marks;
	t_rbroot		*lex_tree;
	t_list			*errors;
	int				error_size;
	int				current_state;
}					t_asm;

t_lex_str		*ft_lex_str_init(void);
t_token			*ft_token_init(void);
t_marks			*ft_marks_init(void);
t_asm			*ft_asm_init(void);
void			ft_error_add(t_asm *asm_data, char *str, int column,\
int error_type);

# define STR_DATA_NUM (asm_data->string_with_data)
# define STR_NUM (asm_data->string_current)
# define CHAMP_DATA (asm_data->champ_data)
# define MARKS (asm_data->marks)
# define LEX_TREE (asm_data->lex_tree)
# define ERROR_LIST (asm_data->errors)
# define ERROR_LIST_SIZE (asm_data->error_size)
# define STATUS_FLAG (asm_data->current_state)

# define CHAMP_NAME (asm_data->champ_data->name)
# define CHAMP_COMMENT (asm_data->champ_data->comment)
# define CHAMP_FLAG (asm_data->champ_data->flag)
# define CHAMP_BRACKETS_OPEN (asm_data->champ_data->open_brackets)
# define CHAMP_BRACKETS_CLOSE (asm_data->champ_data->close_brackets)

# define NAME_COLUMN (asm_data->champ_data->name->num_clomun)
# define NAME_ROW (asm_data->champ_data->name->num_string)
# define NAME_TOKEN (asm_data->champ_data->name->token)
# define NAME_ERROR (asm_data->champ_data->name->error)
# define COMMENT_COLUM (asm_data->champ_data->comment->num_clomun)
# define COMMENT_ROW (asm_data->champ_data->comment->num_string)
# define COMMENT_TOKEN (asm_data->champ_data->comment->token)
# define COMMENT_ERROR (asm_data->champ_data->comment->error)

# define ERROR_STR (((t_error *)(chain->content))->str)
# define ERROR_NUM_STR (((t_error *)(chain->content))->num_str)
# define ERROR_NUM_COLUMN (((t_error *)(chain->content))->num_column)
# define ERROR_TYPE (((t_error *)(chain->content))->type_of_error)

# define WAIT_NAME 1
# define WAIT_COMMENT 2

#endif
