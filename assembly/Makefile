

all: lib
	gcc main.c ft_asm_structs_init.c ft_error_manager.c ft_champ_name_comment.c \
	ft_lexer_champ_code.c ft_fill_tokens.c ft_fill_tokens_newline_and_direct.c \
	ft_lexer_champ_code_helpers.c ft_check_syntax.c tests.c ft_champ_name_comment_extend.c \
	ft_table_of_operations.c ft_create_rows.c ft_solve_sequence_funks.c ft_check_syntax_helpers.c \
	ft_compile.c ft_conver_words.c ft_compile_helpers.c ft_convert_code.c ft_convert_args.c \
	ft_convert_helpers.c -g ../libft/libft.a -I ../libft/includes/ -I ../

lib:
	make -C ../libft/ debug
	make -C ../libft/ clean
