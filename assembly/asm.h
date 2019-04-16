/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:03:00 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/16 21:51:24 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"

/*
char	commands[16][6] = {
	{"live"},
	{"ld"},
	{"st"},
	{"add"},
	{"sub"},
	{"and"},
	{"or"},
	{"xor"},
	{"zjmp"},
	{"ldi"},
	{"sti"},
	{"fork"},
	{"lld"},
	{"lldi"},
	{"lfork"},
	{"aff"}
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
	Separator,
	Comment,
	Whitespace,
	Newline,
	Label,
	Label_arg,
	Command,
	Register,
	Direct,
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

typedef struct	s_errors
{
	char		*error_str;
	int			error_row;
	int			error_column;
	int			error_type;
}				t_errors;

typedef struct	s_machine
{
	int			wait_name;
	int			wait_comment;
	int			double_quotes;
	int			took_name_and_comment;
	int			new_line;
}				t_machine;

/*
** if error flag == 1/2/3 - ошибка лексическая/синтаксическая/семантическая
*/
typedef struct		s_asm_data
{
	int				num_current_row;
	int				num_text_row;
	t_champ_data	*champ_data;
	t_list			*tokens;
	t_machine		*state_machine;
	t_list			*errors;
	int				error_list_size;
	int				error_flag;
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
# define MACHINE_NEW_LINE (asm_data->state_machine->new_line)

# define ERRORS (asm_data->errors)
# define ERROR_SIZE (asm_data->error_list_size)
# define ERROR_FLAG (asm_data->error_flag)

# define T_ERROR_TYPE (((t_errors *)(current->content))->error_type)
# define T_ERROR_STR (((t_errors *)(current->content))->error_str)
# define T_ERROR_COL (((t_errors *)(current->content))->error_column)
# define T_ERROR_ROW (((t_errors *)(current->content))->error_row)

# define TOKEN_DATA ((t_token *)(asm_data->tokens->content))


t_asm_data		*ft_asm_data_init(void);
t_token			*ft_token_init(void);
char			*ft_lexer_champ_data(t_asm_data *asm_data, char *line, int j);
t_errors		*ft_error_init(char *str, int row, int col, int type);
void			ft_error_add(t_asm_data *asm_data, char *line, int column,\
int type);
void			ft_print_errors(t_asm_data *asm_data);
char			*ft_lexer_champ_code(t_asm_data *asm_data, char *line, int j);
void			ft_fill_token(t_asm_data *asm_data, char *line, t_token *token);
void			ft_add_new_str_token(t_asm_data *asm_data);
void			ft_fill_token_direct_labels(t_asm_data *asm_data, char *line, t_token *token);
void			ft_fill_token_direct_digits(t_asm_data *asm_data, char *line, t_token *token);
void			ft_fill_token_direct_regs(t_asm_data *asm_data, char *line, t_token *token);
int				ft_find_sym(char *line, char sym);
int				ft_check_label_symbols(char *line);
int				ft_get_word_len(char *line);
int				ft_string_contain_only_num(char	*str);
int				ft_line_is_command(char *line);
void			ft_print_tokens(t_asm_data *asm_data);

#endif
