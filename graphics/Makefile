# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/25 14:11:47 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../visu

LIB = ../libft/libft.a

FLAGS = -Wall -Wextra -Werror

HEADERS = -I~/Library/Frameworks/SDL2.framework/Headers/ \
	-I ~/Library/Frameworks/SDL2_image.framework/Headers/ \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Headers/ \
	-I ~/Library/Frameworks/SDL2_mixer.framework/Headers/ \
	-I ../ -I ../virtual_machine/ -I ./includes/ -I ../libft/includes/


FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf -framework SDL2_mixer

VM_SRCS_F = core.c args_utils.c check_args.c champions.c read_champions.c \
		read_champions2.c vm.c vm_load.c proccesses.c proc_performe.c \
		proc_utils.c ld.c ldi.c st.c add_sub.c fork_live.c logic.c \
		memory_read.c args_champs.c

VM_DIR = ../virtual_machine/

VM_SRCS = $(addprefix $(VM_DIR), $(VM_SRCS_F))

GRAPH_SRCS = visu_events.c visu_init.c visu_load.c visu_main.c visu_make.c \
		visu_print.c visu_render_carrier.c visu_render.c

GRAPH_TESTS = visu_tests.c

OBJ = $(GRAPH_SRCS:.c=.o) $(VM_SRCS:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	make -C ../libft/

$(NAME): $(OBJ)
	gcc $(FLAGS) $(HEADERS) $(OBJ) $(LIB) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	@gcc $(FLAGS) $(HEADERS) -F ~/Library/Frameworks/ -c $< -o $@

tests:
	gcc $(FLAGS) $(HEADERS) $(OBJ) $(LIB) $(FRAMEWORKS) $(GRAPH_TESTS) -o $(NAME)

clean:
	make -C ../libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C ../libft/ fclean
	rm -f $(NAME)

re: fclean all
