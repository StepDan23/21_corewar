# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/25 14:15:03 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = asm

NAME_2 = corewar

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
