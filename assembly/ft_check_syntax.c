/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:09:07 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/17 21:18:59 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	g_comms[REG_NUMBER][6] = {
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
};

void	ft_check_syntax(t_asm_data *asm_data)
{
	t_table_ops	*ops;
	t_token		*token;
	t_list		*labels;
	int			i;

	i = 0;
	ops = ft_table_operations_init();
	while (i < asm_data->token_size)
	{
		token = (t_token *)(asm_data->tokens->content);
	}
}
