
#
#	Compiler variables
#

CC= gcc -g
CC_FLAGS= -Wall -Wextra -Werror

#
#	Debug compiler variables
#

DG_CC_FLAGS= g -o0

#
#	Release variables
#

NAME= libft.a
HEADER= libft.h
HEADERDIR= includes
SRCSDIR= src
OBJ= *.o
SRCS= $(OBJS: .o=.c)
FLAGS = -c -g -I ./$(HEADERDIR)

all: $(NAME)

#
#	Debug mode settings
#

debug: CC_FLAGS += $(DG_CC_FLAGS)
debug: $(NAME)

#
#	Release mode
#

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ):
	@gcc $(CC_FLAGS) $(FLAGS) ./src/*.c


#
#	Clean
#

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

