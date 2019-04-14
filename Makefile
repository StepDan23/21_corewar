# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/14 11:40:15 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu

LIB = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers

FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf 

GRAPH_SRCS_F = *.c

GRAPH_DIR = graphics/

GRAPH_SRCS = $(addprefix $(GRAPH_DIR), $(GRAPH_SRCS_F))

all: $(LIB)
	gcc $(FLAGS) $(GRAPH_SRCS) $(LIB) $(HEADERS) $(FRAMEWORKS) -o $(NAME)

$(LIB):
	make -C ./libft/

clean:
	make -C ./libft/ clean
	rm -f

fclean:
	make -C ./libft/ fclean
	rm -f $(NAME)

re: fclean all
