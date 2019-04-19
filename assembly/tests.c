

#include "asm.h"
#include <stdio.h>

void	ft_print_tokens(t_asm_data *asm_data)
{
	t_list	*current;
	t_list	*temp;
	t_token	*token;

	printf("\n\n\n\n");
	current = asm_data->tokens;
	while(current)
	{
		token = ((t_token *)(current->content));
		printf("{%s} %d\n", token->str, token->type);
		current = current->next;
	}
}

void	ft_print_labels(t_asm_data *asm_data, t_list *labels)
{
	t_list	*current;
	t_label_compile	*label;

	printf("\n\n\n\n");

	current = labels;
	while (current)
	{
		label = (t_label_compile *)(current->content);
		printf("label_text = %s, row_num = %d, points_to_row = %d, ", label->label_text, label->row_num, label->points_to_row);
		printf("label_num = %zu\n", current->content_size);
		current = current->next;
	}
}