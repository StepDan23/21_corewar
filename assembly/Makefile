

all: lib
	gcc main.c ft_asm_structs_init.c ft_error_manager.c ft_champ_name_comment.c\
	 -g ../libft/libft.a -I ../libft/includes/ -I ../

lib:
	make -C ../libft/ debug
	make -C ../libft/ clean
