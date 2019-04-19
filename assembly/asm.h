/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:03:00 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/19 13:10:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "op.h"

typedef enum		e_types
{
	Unknown = -1,
	Separator,
	Whitespace,
	Newline,
	Label,
	Label_arg,
	Command,
	Register,
	Direct_label,
	Direct_number,
	Number
}					t_types;

typedef struct		s_table_ops
{
	int				*command_nums;
	int				*count_of_args;
	int				*arg1_type;
	int				*arg2_type;
	int				*arg3_type;
	int				*arg_code_exists;
}					t_table_ops;

typedef struct		s_syntax_row
{
	int				row_num;
	int				command_num;
	int				command_size;
	int				num_current_arg;
	int				wait_separator;
	int				newline;
	t_types			prev_arg_type;
	char			**args_text;
	int				arg_types_code;
}					t_syntax_row;

# define ROW_NUM (row->row_num)
# define ROW_COM_NUM (row->command_num)
# define ROW_CNT_MAX (row->command_size)
# define ROW_CNT_ARG (row->num_current_arg)
# define ROW_WAIT_SEP (row->wait_separator)
# define ROW_NEWLINE (row->newline)
# define PREV_ARG_TYPE (row->prev_arg_type)
# define ROW_ARGS_TEXT (row->args_text)
# define ROW_ARG_CODE (row->arg_types_code)

typedef struct		s_label_compile
{
	int				row_num;
	int				points_to_row;
	char			*label_text;
}					t_label_compile;

# define LABEL_TEXT (((t_label_compile *)(current->content))->label_text)

typedef struct		s_token
{
	char			*str;
	t_types			type;
	int				col;
	int				row;
}					t_token;

# define TOKEN_STR ((t_token *)(asm_data->tokens->content)->str)
# define TOKEN_TYPE ((t_token *)(asm_data->tokens->content)->row)
# define TOKEN_COL ((t_token *)(asm_data->tokens->content)->col)
# define TOKEN_ROW ((t_token *)(asm_data->tokens->content)->row)

# define TOKEN_DATA ((t_token *)(asm_data->tokens->content))

# define TKN_STR (token->str)
# define TKN_TYPE (token->type)
# define TKN_COL (token->col)
# define TKN_ROW (token->row)

typedef struct	s_champ_data
{
	char		*champ_name;
	int			name_row;
	int			name_column;
	char		*champ_comment;
	int			comment_row;
	int			comment_column;
}				t_champ_data;

# define CHAMP_NAME (asm_data->champ_data->champ_name)
# define CHAMP_COMMENT (asm_data->champ_data->champ_comment)
# define CHAMP_NAME_ROW (asm_data->champ_data->name_row)
# define CHAMP_NAME_COL (asm_data->champ_data->name_column)
# define CHAMP_COMMENT_ROW (asm_data->champ_data->comment_row)
# define CHAMP_COMMENT_COL (asm_data->champ_data->comment_column)

typedef struct	s_errors
{
	char		*error_str;
	int			error_row;
	int			error_column;
	int			error_type;
}				t_errors;

# define ERRORS (asm_data->errors)
# define ERROR_SIZE (asm_data->error_list_size)
# define ERROR_FLAG (asm_data->error_flag)

# define T_ERROR_TYPE (((t_errors *)(current->content))->error_type)
# define T_ERROR_STR (((t_errors *)(current->content))->error_str)
# define T_ERROR_COL (((t_errors *)(current->content))->error_column)
# define T_ERROR_ROW (((t_errors *)(current->content))->error_row)

typedef struct	s_machine
{
	int			wait_name;
	int			wait_comment;
	int			double_quotes;
	int			took_name_and_comment;
	int			new_line;
	int			one_valid_command;
}				t_machine;

# define MACHINE_WAIT_NAME (asm_data->state_machine->wait_name)
# define MACHINE_WAIT_COMMENT (asm_data->state_machine->wait_comment)
# define MACHINE_DOUBLE_QUOTES (asm_data->state_machine->double_quotes)
# define MACHINE_NAME_COMMENT (asm_data->state_machine->took_name_and_comment)
# define MACHINE_NEW_LINE (asm_data->state_machine->new_line)
# define MACHINE_VALID_CODE (asm_data->state_machine->one_valid_command)
/*
** if error flag == 1/2/3 - ошибка лексическая/синтаксическая/семантическая
*/
typedef struct		s_asm_data
{
	int				count_symbols;
	int				num_current_row;
	int				num_text_row;
	t_champ_data	*champ_data;
	t_list			*tokens;
	int				token_size;
	t_machine		*state_machine;
	t_list			*errors;
	int				error_list_size;
	int				error_flag;
	t_list			*syntax_row;
	int				num_syntax_row;
	t_list			*label_temp;
	int				num_label_temp;
}					t_asm_data;

# define ASM_TOKENS (asm_data->tokens)
# define ASM_NUM_ROW (asm_data->num_current_row)
# define ASM_NUM_TEXT_ROW (asm_data->num_text_row)
# define ASM_CHAMP_DATA (asm_data->champ_data)
# define ASM_STATE_MACHINE (asm_data->state_machine)
# define ASM_TOKEN_SIZE (asm_data->token_size)
# define ASM_SYNTAX_ROW (asm_data->syntax_row)
# define ASM_SYNTAX_ROW_COUNT (asm_data->num_syntax_row)

# define T_REGS 1
# define T_DIRS 10
# define T_INDS 100

t_asm_data		*ft_asm_data_init(void);
t_token			*ft_token_init(void);
char			*ft_lexer_champ_data(t_asm_data *asm_data, char *line, int j);
t_errors		*ft_error_init(char *str, int row, int col, int type);
void			ft_error_add(t_asm_data *asm_data, char *line, int column,\
int type);
void	ft_error_token(t_asm_data *asm_data, char *line, int row, int column,\
int type);
void			ft_print_errors(t_asm_data *asm_data);
char			*ft_lexer_champ_code(t_asm_data *asm_data, char *line, int j);
void			ft_fill_token(t_asm_data *asm_data, char *line, t_token *token);
void			ft_add_new_str_token(t_asm_data *asm_data);
void			ft_fill_token_direct_labels(t_asm_data *asm_data, char *line,\
t_token *token);
void			ft_fill_token_direct_digits(t_asm_data *asm_data, char *line,\
t_token *token);
int				ft_find_sym(char *line, char sym);
int				ft_check_label_symbols(char *line);
void			ft_check_syntax(t_asm_data *asm_data);
int				ft_get_word_len(char *line);
int				ft_string_contain_only_num(char	*str);
int				ft_line_is_command(char *line);
void			ft_current_func_divis(t_asm_data *asm_data, char *line, int i,\
int j);
t_table_ops		*ft_table_operations_init(void);
t_label_compile	*ft_init_label_compile(void);
t_syntax_row	*ft_syn_row_init(void);
void			ft_fill_strings(t_asm_data *asm_data, t_token *token,\
t_list *labels);
int				ft_token_type_value(t_types value);
int				ft_is_arg_valid(t_types type, int cur_arg, int com_num,\
t_token *token);
void			ft_add_new_command_row(t_asm_data *asm_data, t_token *token,\
t_syntax_row *row);
void			ft_fill_row(t_asm_data *asm_data, t_token *token,\
t_list *labels, t_syntax_row *row);
t_list			*ft_collect_labels(t_asm_data *asm_data, int i, int j);
void			ft_row_args_check(t_asm_data *asm_data, t_token *token,\
t_list *labels, t_syntax_row *row);
void			ft_check_syntax_rows(t_asm_data *asm_data, t_list *rows);


void			ft_print_labels(t_asm_data *asm_data, t_list *labels);
void			ft_print_tokens(t_asm_data *asm_data);

#endif
