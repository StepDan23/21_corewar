/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_champ_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:46:59 by how_r_u           #+#    #+#             */
/*   Updated: 2019/04/16 15:38:58 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
	в этой секции нужно проверять:
	имя команды,
	ее атрибуты,
	метки,
	! Проверять тип элемента последовательно - %, потом число потом комманду.
	! Сделать паровоз из функций

	! Если входим в новую строку, то сразу добавляем токен с типом новой строки - придумать как
*/

int		ft_find_sym(char *line, char sym)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] != sym) && line[i] != COMMENT_CHAR)
		i++;
	if (line[i] && line[i] != COMMENT_CHAR)
		return (i);
	else
		return (0);
}

int		ft_check_label_sym(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != ':')
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (LABEL_CHARS[j] == line[i])
				break ;
			j++;
		}
		if (!LABEL_CHARS[j])
			return (0);
		i++;
	}
	return (1);
}

int		ft_get_word_len(char *line)
{
	int	i;

	i = 0;
	if (line[0] == LABEL_CHAR)
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && \
	line[i] != COMMENT_CHAR && line[i] != LABEL_CHAR &&
	line[i] != SEPARATOR_CHAR)
		i++;
	if (line[0] == SEPARATOR_CHAR && i == 0)
		i++;
	if (i > 0)
	{
		ft_printf("\n WORD len = %i ", i);
		return (i);
	}
	if (line[i] == ' ' || line[i] == '\t')
		return (1);
	return (0);
}

int		ft_string_contain_only_num(char	*str)
{
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == 0)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (str[i] != '+' || str[i] != '-'))
			return (0);
		i++;
	}
	return (1);
}



void	ft_fill_token3(t_asm_data *asm_data, char *line)
{
	long long	temp;

	if (line[0] == 'r')
	{
		if (ft_string_contain_only_num(&line[1]))
		{
			temp = ft_atol(&line[1]);
			if (temp > 0 && temp < REG_NUMBER)
				TOKEN_DATA->type = Register;
			else
			{
				TOKEN_DATA->type = Unknown;
				ft_error_add(asm_data, ft_strjoin_orig("Wrong reg num ",\
				line), TOKEN_DATA->col, 1);
			}
		}
		else
		{
			TOKEN_DATA->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Detected char in reg ",\
			line), TOKEN_DATA->col, 1);
		}
		return ;
	}
	//ft_fill_token3(asm_data, line);
}

void	ft_fill_token2(t_asm_data *asm_data, char *line)
{
	if (line[0] == DIRECT_CHAR)
	{

	}
}

void	ft_fill_token(t_asm_data *asm_data, char *line)
{
	ft_printf("%s ", line);
	TOKEN_DATA->str = line;
	if (line[0] == ' ' || line[0] == '\t')
	{
		TOKEN_DATA->type = Whitespace;
		return ;
	}
	if (line[0] == SEPARATOR_CHAR)
	{
		TOKEN_DATA->type = Separator;
		return ;
	}
	if (ft_find_sym(line, LABEL_CHAR))
	{
		if (ft_check_label_sym(line))
			TOKEN_DATA->type = Label;
		else
		{
			TOKEN_DATA->type = Unknown;
			ft_error_add(asm_data, ft_strjoin_orig("Wrong symbols in label ",\
			line), TOKEN_DATA->col, 1);
		}
		return ;
	}
	ft_fill_token2(asm_data, line);
}

void	ft_add_new_str_token(t_asm_data *asm_data)
{
	t_token	*token;
	t_list	*chain;

	chain = ft_lstnew(NULL, sizeof(t_token));
	token = ft_token_init();
	if (ASM_TOKENS == NULL)
		ASM_TOKENS = chain;
	else
		ft_lstadd_last(&ASM_TOKENS, chain);
	token->row = ASM_NUM_ROW - 1;
	token->col = 0;
	token->str = "\n";
	token->type = Newline;
	MACHINE_NEW_LINE = 1;
}

char	*ft_lexer_champ_code(t_asm_data *asm_data, char *line)
{
	int		i;
	int		word_len;
	t_token	*token;
	t_list	*chain;

	i = 0;
	ft_putendl(line);
	if (!MACHINE_NEW_LINE)
		ft_add_new_str_token(asm_data);
	while (line[i])
	{
		word_len = ft_get_word_len(&line[i]);
		chain = ft_lstnew(NULL, sizeof(t_token));
		token = ft_token_init();
		chain->content = token;
		ft_lstadd_last(&ASM_TOKENS, chain);
		token->row = ASM_NUM_ROW;
		token->col = i;
		ft_fill_token(asm_data, ft_strsub(line, i, word_len));
		i += word_len;
	}
	return (line);
}
