/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemiy <artemiy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:57:58 by fkuhn             #+#    #+#             */
/*   Updated: 2019/04/07 22:04:07 by artemiy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETST_H
# define TETST_H
# include "vm.h"

void	vm_init_memory(unsigned char *memory);
void	proccess_init_reg(unsigned int *reg);

#endif