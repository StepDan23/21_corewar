
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

//0-10
typedef enum		e_types
{
	Unknown = -1,
	None = 0,
	Comment,
	Whitespace,
	Newline,
	Label,
	Command,
	Register,
	Symbol,
	String,
	Number
}					t_types;

typedef struct		s_token
{
	char			*str;
	t_types			type;
	int				col;
	int				row;
}					t_token;

typedef struct	s_champ_data
{
	char		*champ_name;
	int			name_row;
	int			name_column;
	char		*champ_comment;
	int			comment_row;
	int			comment_column;
}				t_champ_data;

typedef struct	s_machine
{
	int			wait_name;
	int			wait_comment;
	int			double_quotes;
	int			took_name_and_comment;
}				t_machine;

typedef struct		s_asm_data
{
	int				num_current_row;
	int				num_text_row;
	t_champ_data	*champ_data;
	t_list			*tokens;
	t_machine		*state_machine;
}					t_asm_data;

# define ASM_TOKENS (asm_data->tokens)
# define ASM_NUM_ROW (asm_data->num_current_row)
# define ASM_NUM_TEXT_ROW (asm_data->num_text_row)
# define ASM_CHAMP_DATA (asm_data->champ_data)
# define ASM_STATE_MACHINE (asm_data->state_machine)

# define TOKEN_STR ((t_token *)(asm_data->tokens->content)->str)
# define TOKEN_TYPE
# define TOKEN_COL ((t_token *)(asm_data->tokens->content)->col)
# define TOKEN_ROW ((t_token *)(asm_data->tokens->content)->row)

# define CHAMP_NAME (asm_data->champ_data->champ_name)
# define CHAMP_COMMENT (asm_data->champ_data->champ_comment)
# define CHAMP_NAME_ROW (asm_data->champ_data->name_row)
# define CHAMP_NAME_COL (asm_data->champ_data->name_column)
# define CHAMP_COMMENT_ROW (asm_data->champ_data->comment_row)
# define CHAMP_COMMENT_COL (asm_data->champ_data->comment_column)

# define MACHINE_WAIT_NAME (asm_data->state_machine->wait_name)
# define MACHINE_WAIT_COMMENT (asm_data->state_machine->wait_comment)
# define MACHINE_DOUBLE_QUOT (asm_data->state_machine->double_quotes)
# define MACHINE_NAME_COMMENT (asm_data->state_machine->took_name_and_comment)

t_asm_data		*ft_asm_data_init(void);
t_token			*ft_token_init(int col, int row, char *str, t_types type);


#endif
