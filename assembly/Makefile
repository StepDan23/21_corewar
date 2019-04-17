

all: lib
	gcc main.c ft_asm_structs_init.c ft_error_manager.c ft_champ_name_comment.c\
	 ft_lexer_champ_code.c ft_fill_tokens.c ft_fill_tokens_newline_and_direct.c \
	ft_lexer_champ_code_helpers.c ft_check_syntax.c tests.c ft_champ_name_comment_extend.c\
	 ft_table_of_operations.c -g ../libft/libft.a -I ../libft/includes/ -I ../

lib:
	make -C ../libft/ debug
	make -C ../libft/ clean
