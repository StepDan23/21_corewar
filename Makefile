# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/15 14:28:02 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu

LIB = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers/ \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers/ \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers/ \
	-I ./ -I ./virtual_machine/ -I ./graphics/includes/ -I ./libft/includes/

FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf 

GRAPH_SRCS_F = *.c

GRAPH_DIR = graphics/

GRAPH_SRCS = $(addprefix $(GRAPH_DIR), $(GRAPH_SRCS_F))

all: $(LIB)
	gcc $(HEADERS) $(FLAGS) $(GRAPH_SRCS) $(LIB) $(FRAMEWORKS) -o $(NAME)

$(LIB):
	make -C ./libft/

clean:
	make -C ./libft/ clean
	rm -f

fclean:
	make -C ./libft/ fclean
	rm -f $(NAME)

re: fclean all
