NAME = ../corewar
LIB = ../libft/libft.a
FLAGS = -Werror -Wall -Wextra -g
GCC = gcc
SRC = core.c vm_main.c args_utils.c check_args.c champions.c read_champions.c read_champions2.c vm.c vm_load.c proccesses.c proc_performe.c proc_utils.c ld.c ldi.c st.c add_sub.c fork_live.c logic.c\
		memory_read.c args_champs.c
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

test: $(LIB) $(OBJ) operations_tests.c
	$(GCC) $(FLAGS) -c operations_tests.c -o operations_tests.o -I../libft/includes -I.. -I.
	$(GCC) $(FLAGS) args_utils.c args_champs.c check_args.o champions.o read_champions.o read_champions2.o vm.c vm_load.o \
	proccesses.o proc_performe.o proc_utils.o ld.o ldi.o st.o add_sub.o fork_live.o logic.o operations_tests.o memory_read.c core.c \
	-I../libft/includes -I.. -I. -L ../libft -lft -o test