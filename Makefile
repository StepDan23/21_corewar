# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/24 20:08:54 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu

LIB = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers/ \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers/ \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers/ \
	-I ~/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers/ \
	-I ./ -I ./virtual_machine/ -I ./graphics/includes/ -I ./libft/includes/


FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf -framework SDL2_mixer

VM_SRCS_F = core.c args_utils.c check_args.c champions.c read_champions.c read_champions2.c vm.c vm_load.c proccesses.c proc_performe.c proc_utils.c ld.c ldi.c st.c add_sub.c fork_live.c logic.c\
		memory_read.c args_champs.c
VM_DIR = virtual_machine/

VM_SRCS = $(addprefix $(VM_DIR), $(VM_SRCS_F))

GRAPH_SRCS_F = *.c

GRAPH_DIR = graphics/

GRAPH_SRCS = $(addprefix $(GRAPH_DIR), $(GRAPH_SRCS_F))

all: $(LIB)
	gcc  -g $(HEADERS) $(GRAPH_SRCS) $(VM_SRCS) $(LIB) $(FRAMEWORKS) -o $(NAME)

$(LIB):
	make -C ./libft/

clean:
	make -C ./libft/ clean
	make -C ./virtual_machine/ clean
	rm -f

fclean:
	make -C ./libft/ fclean
	make -C ./virtual_machine/ fclean
	rm -f $(NAME)

re: fclean all
