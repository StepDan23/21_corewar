

#include "asm.h"
#include <stdio.h>

void	ft_print_tokens(t_asm_data *asm_data)
{
	t_list	*current;
	t_list	*temp;
	t_token	*token;

	printf("\n\n");
	current = asm_data->tokens;
	printf("Test tokens: \n");
	while(current)
	{
		token = ((t_token *)(current->content));
		printf("{%s} %d\n", token->str, token->type);
		current = current->next;
	}
}

void	test_print_labels(t_asm_data *asm_data, t_list *labels)
{
	t_list	*current;
	t_label_compile	*label;

	printf("\n\n");

	current = labels;
	printf("Test labels: \n");

	while (current)
	{
		label = (t_label_compile *)(current->content);
		printf("label_text = %s, row_num = %d, points_to_row = %d, ", label->label_text, label->row_num, label->points_to_row);
		printf("label_num = %zu\n", current->content_size);
		current = current->next;
	}
	printf("\n\n");
}

void	test_print_rows(t_asm_data *asm_data)
{
	t_list	*current;
	t_syntax_row *row;
	int				i = -1;
	int				j = 0;

	current = ASM_SYNTAX_ROW;
	while (current && j < ASM_SYNTAX_ROW_COUNT)
	{
		row = (t_syntax_row *)(current->content);
		i = -1;
		while (++i < ROW_CNT_ARG - 1)
			printf("arg_text = %s, arg_size = %d, arg_type = %d\n", ROW_ARGS_TEXT[i], ROW_ARGS_SIZES[i], ROW_ARG_TYPES[i]);
		printf("Current count = %d, estimated count = %d, arg_code = %d\n", ROW_CNT_ARG - 1, ROW_CNT_MAX, ROW_ARG_CODE);
		printf("Row num = %d, ROW_SIZE = %d, ROW_CODE_PLACE = %d\n", ROW_NUM, ROW_CODE_SIZE,ROW_CODE_PLACE);
		current = current->next;
		j++;
		printf("\n");
	}
	printf("\n\n");

}
