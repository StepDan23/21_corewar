# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/01 18:38:37 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ../libft/libft.a

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-I ~/SDL_gfx/

FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf

all: $(LIB)
	gcc *.c ../libft/libft.a $(HEADERS) $(FRAMEWORKS)

$(LIB):
	make -C ../libft/

clean:
	make -C ../libft/ clean
