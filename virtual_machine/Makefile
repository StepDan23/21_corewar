NAME = corewar
LIB = ../libft/libft.a
FLAGS = -Werror -Wall -Wextra -g
GCC = gcc
SRC = check_args.c core.c champions.c read_champions.c read_champions2.c vm.c vm_load.c proccesses.c
OBJ = $(SRC:.c=.o)
#  core.c 
all: $(LIB) $(NAME)

$(LIB):
	@make -C ../libft/ all

$(NAME): $(OBJ)
	@$(GCC) $(FLAGS) $(OBJ) -L ../libft -lft -o $(NAME)

%.o: %.c
	@$(GCC) $(FLAGS) -c -g $< -o $@ -I../libft/includes -I..

clean:
	rm -f *.o
	make -C ../libft/ clean
fclean: clean
	rm -f $(NAME)
	make -C ../libft/ fclean
re: fclean all