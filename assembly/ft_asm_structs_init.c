/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asm_structs_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:00:35 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/15 13:47:44 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

t_token			*ft_token_init(int col, int row, char *str, t_types type)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->col = col;
	token->row = row;
	token->str = str;
	token->type = type;
	return (token);
}

t_champ_data	*ft_champ_data_init(void)
{
	t_champ_data	*champ_data;

	champ_data = (t_champ_data *)malloc(sizeof(t_champ_data));
	if (!champ_data)
		exit(1);
	champ_data->champ_name = (char *)malloc(PROG_NAME_LENGTH);
	champ_data->champ_comment = (char *)malloc(COMMENT_LENGTH);
	champ_data->comment_column = 0;
	champ_data->comment_row = 0;
	champ_data->name_column = 0;
	champ_data->name_row = 0;
	return (champ_data);
}

t_errors		*ft_error_init(char *str, int row, int col, int type)
{
	t_errors	*error_data;

	error_data = (t_errors *)malloc(sizeof(t_errors));
	if (!error_data)
		exit(1);
	error_data->error_str = str;
	error_data->error_row = row;
	error_data->error_column = col;
	error_data->error_type = type;
	return (error_data);
}

t_machine		*ft_state_machine_init(void)
{
	t_machine	*state_machine;

	state_machine = (t_machine *)malloc(sizeof(t_machine));
	if (!state_machine)
		exit(1);
	state_machine->wait_name = 0;
	state_machine->wait_comment = 0;
	state_machine->double_quotes = 0;
	state_machine->took_name_and_comment = 0;
	return (state_machine);
}

t_asm_data		*ft_asm_data_init(void)
{
	t_asm_data		*asm_data;

	asm_data = (t_asm_data *)malloc(sizeof(t_asm_data));
	if (!asm_data)
		exit(1);
	asm_data->num_current_row = 1;
	asm_data->num_text_row = 1;
	asm_data->tokens = NULL;
	asm_data->state_machine = ft_state_machine_init();
	asm_data->champ_data = ft_champ_data_init();
	asm_data->errors = NULL;
	return (asm_data);
}
