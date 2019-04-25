# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 18:31:12 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/25 16:41:02 by lshanaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = corewar

NAME_2 = asm

NAME_3 = visu

all: 
	make -C ./virtual_machine
	make -C ./assembly
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
