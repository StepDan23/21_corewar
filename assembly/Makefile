#
#	Compiler variables
#

CC= gcc -ggdb
CC_FLAGS= -Wall -Wextra -Werror
NAME_ASM = ../asm
NAME_DEASM = ../dizasm
LIB_DIR = ../libft/includes
HEADERDIR = ../
SRC = main.c ft_asm_structs_init.c ft_error_manager.c ft_champ_name_comment.c \
	ft_lexer_champ_code.c ft_fill_tokens.c ft_fill_tokens_newline_and_direct.c \
	ft_lexer_champ_code_helpers.c ft_check_syntax.c ft_champ_name_comment_extend.c \
	ft_table_of_operations.c ft_create_rows.c ft_solve_sequence_funks.c ft_check_syntax_helpers.c \
	ft_compile.c ft_conver_words.c ft_compile_helpers.c ft_convert_code.c ft_convert_args.c \
	ft_convert_helpers.c ft_clear_data.c 
CH_SRC = ft_dizasm_name_comment.c ft_dizasm_solve_args.c ft_dizasm.c ft_dizasm_helpers.c
OBJ= $(SRC:.c=.o)
OBJ_D= $(CH_SRC:.c=.o)


LIB=../libft/libft.a


#
#	Debug mode settings
#

#debug: CC_FLAGS += $(DG_CC_FLAGS)
#debug: $(NAME)

#
#	Release mode
#

all: $(NAME_ASM)

$(NAME_ASM): $(OBJ) $(OBJ_D)
	@make -C ../libft/ 
	@make -C ../libft/ clean
	@$(CC) $(CC_FLAGS) $(OBJ) $(LIB) -I $(LIB_DIR) -I ../ -o $(NAME_ASM)
	@$(CC) $(CC_FLAGS) $(OBJ_D) $(LIB) -I $(LIB_DIR) -I ../ -o $(NAME_DEASM)

%.o : %.c
	@$(CC)  $(FLAGS) -I $(LIB_DIR) -I ../ -c $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME_ASM)
	rm -rf $(NAME_DEASM)

re: fclean all
