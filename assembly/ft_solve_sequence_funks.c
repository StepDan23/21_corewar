/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_sequence_funks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:34:53 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 15:55:09 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	ft_check_last_row(t_asm_data *asm_data, int fd, int i)
{
	char		*str;
	t_list		*chain;
	t_token		*token;

	str = ft_strnew(31);
	lseek(fd, (off_t)(asm_data->count_symbols - 10), 0);
	read(fd, str, 30);
	while (str[i] == 0 || str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '\n')
	{
		chain = ft_lstnew(NULL, sizeof(t_token));
		token = ft_token_init();
		asm_data->token_size += 1;
		chain->content = token;
		if (asm_data->tokens)
			ft_lstadd_last(asm_data->tokens, chain);
		else
			asm_data->tokens = chain;
		token->str = ft_strdup("\n");
		token->type = Newline;
	}
	else
		ft_error_add(asm_data, ft_strdup("Add newline after last row "), 0, 2);
	free(str);
}

void	ft_check_main_params_exists(t_asm_data *asm_data)
{
	if (!(MACHINE_NAME_COMMENT & 1))
		ft_error_add(asm_data, ft_strdup("No Champ's name founded "), 0, 3);
	if (!(MACHINE_NAME_COMMENT & 2))
		ft_error_add(asm_data, ft_strdup("No Champ's comment founded "), 0, 3);
	if (!MACHINE_VALID_CODE)
		ft_error_add(asm_data, ft_strdup("No commands were founed. Add one "),\
		0, 3);
}

void	ft_row_wrapper(t_syntax_row *row)
{
	ROW_WAIT_SEP = 1;
	ROW_CNT_ARG++;
}
