/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_of_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:59:19 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/22 20:23:54 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

int				g_command_nums[REG_NUMBER] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,\
	11, 12, 13, 14, 15, 16};

int				g_count_of_args[REG_NUMBER] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3,\
	3, 1, 2, 3, 1, 1};

int				g_arg1_type[REG_NUMBER] = {
	T_DIRS,
	T_DIRS + T_INDS,
	T_REGS,
	T_REGS,
	T_REGS,
	T_REGS + T_DIRS + T_INDS,
	T_REGS + T_DIRS + T_INDS,
	T_REGS + T_DIRS + T_INDS,
	T_DIRS,
	T_REGS + T_DIRS + T_INDS,
	T_REGS,
	T_DIRS,
	T_DIRS + T_INDS,
	T_REGS + T_DIRS + T_INDS,
	T_DIRS,
	T_REGS
};

int				g_arg2_type[REG_NUMBER] = {
	0,
	T_REGS,
	T_REGS + T_INDS,
	T_REGS,
	T_REGS,
	T_REGS + T_DIRS + T_INDS,
	T_REGS + T_DIRS + T_INDS,
	T_REGS + T_DIRS + T_INDS,
	0,
	T_REGS + T_DIRS,
	T_REGS + T_DIRS + T_INDS,
	0,
	T_REGS,
	T_REGS + T_DIRS,
	0,
	0
};

int				g_arg3_type[REG_NUMBER] = {
	0,
	0,
	0,
	T_REGS,
	T_REGS,
	T_REGS,
	T_REGS,
	T_REGS,
	0,
	T_REGS,
	T_REGS + T_DIRS,
	0,
	0,
	T_REGS,
	0,
	0
};

int				g_args_codes[REG_NUMBER] = {
	0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1
};

int				g_t_dir_coefs[REG_NUMBER] = {
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1
};

t_table_ops		*ft_table_operations_init(void)
{
	t_table_ops	*operations;

	operations = (t_table_ops *)malloc(sizeof(t_table_ops));
	if (!operations)
		exit(ft_printf("error in malloc ft_table_operations_init()\n"));
	operations->command_nums = g_command_nums;
	operations->count_of_args = g_count_of_args;
	operations->arg1_type = g_arg1_type;
	operations->arg2_type = g_arg2_type;
	operations->arg3_type = g_arg3_type;
	operations->arg_code_exists = g_args_codes;
	operations->t_dir_coefs = g_t_dir_coefs;
	return (operations);
}

t_label_compile	*ft_init_label_compile(void)
{
	t_label_compile	*label;

	label = (t_label_compile *)malloc(sizeof(t_label_compile));
	if (!label)
		exit(1);
	label->points_to_row = -5;
	label->label_text = NULL;
	label->row_num = 0;
	label->row = NULL;
	return (label);
}

t_syntax_row	*ft_syn_row_init(void)
{
	t_syntax_row	*row;

	row = (t_syntax_row *)malloc(sizeof(t_syntax_row));
	if (!row)
		exit(ft_printf("error in malloc ft_syn_row_init()\n"));
	row->row_num = 0;
	row->command_num = -2;
	row->command_size = 0;
	row->num_current_arg = 1;
	row->wait_separator = 0;
	row->newline = 0;
	row->prev_arg_type = -5;
	row->args_text = NULL;
	row->arg_types_code = 0;
	row->size_of_args = NULL;
	row->arg_types = NULL;
	row->code_place = 0;
	row->code_size = 0;
	row->t_dir_coef = 0;
	return (row);
}

t_list			*ft_collect_labels(t_asm_data *asm_data, int i, int j)
{
	t_list			*current;
	t_list			*root;
	t_list			*chain;
	t_label_compile	*label;

	root = NULL;
	current = asm_data->tokens;
	while (++i <= ASM_TOKEN_SIZE)
	{
		if (((t_token *)(current->content))->type == Label)
		{
			label = ft_init_label_compile();
			label->row_num = ((t_token *)(current->content))->row;
			label->label_text = ft_strdup(((t_token *)(current->content))->str);
			chain = ft_lstnew(NULL, 0);
			chain->content = label;
			chain->content_size = j++;
			if (!root)
				root = chain;
			else
				ft_lstadd_last(root, chain);
		}
		current = current->next;
	}
	return (root);
}

void			ft_merge_in_ecstasy(t_asm_data *asm_data, t_syntax_row *row)
{
	t_list			*current_label;
	t_list			*last_label;
	t_label_compile	*label_data;

	current_label = ASM_LABEL;
	while (current_label)
	{
		label_data = (t_label_compile *)current_label->content;
		label_data->points_to_row = ROW_NUM;
		label_data->row = row;
		last_label = current_label;
		current_label = current_label->next;
		free(last_label);
	}
	ASM_NUM_LABEL = 0;
	ASM_LABEL = NULL;
}
