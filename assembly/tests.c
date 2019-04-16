

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