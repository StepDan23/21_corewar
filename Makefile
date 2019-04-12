# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/12 16:05:50 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ./libft/libft.a

LIB_GFX = ~/SDL_gfx/libsdl_gfx.a

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-I ~/SDL_gfx/

FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf 

GRAPH_SRCS_F = *.c

GRAPH_DIR = graphics/

GRAPH_SRCS = $(addprefix $(GRAPH_DIR), $(GRAPH_SRCS_F))

all: $(LIB) $(LIB_GFX)
	gcc $(GRAPH_SRCS) $(LIB) $(LIB_GFX) $(HEADERS) $(FRAMEWORKS)

$(LIB):
	make -C ./libft/

$(LIB_GFX):
	gcc -c ~/SDL_gfx/*.c -F ~/Library/Frameworks/
	ar rcs $(LIB_GFX) SDL2_framerate.o SDL2_gfxPrimitives.o SDL2_imageFilter.o SDL2_rotozoom.o
	ranlib $(LIB_GFX)

clean:
	make -C ../libft/ clean
