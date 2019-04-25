# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/25 16:05:17 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = corewar

NAME_2 = asm

NAME_3 = visu

all: $(NAME_1) $(NAME_2)

$(NAME_1):
	make -C ./virtual_machine

$(NAME_2):
	make -C ./assembly

$(NAME_3):
	make -C ./graphics

clean:
	make -C ./virtual_machine clean
	make -C ./graphics clean
	make -C ./assembly clean

fclean:
	make -C ./virtual_machine fclean
	make -C ./graphics fclean
	make -C ./assembly fclean

re: fclean all
