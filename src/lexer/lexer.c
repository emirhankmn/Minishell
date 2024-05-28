/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:57 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:53:59 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../header/minishell.h"

static t_token	*get_tokens(char *input)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (input && input[i])
	{
		if (get_token_pipe(input, &i, &tokens) == FAILURE)
			break ;
		if (get_token_bracket(input, &i, &tokens) == FAILURE)
			break ;
		if (get_token_redirection(input, &i, &tokens) == FAILURE)
			break ;
		if (get_token_quote(input, &i, &tokens) == FAILURE)
			break ;
		if (get_token_text(input, &i, &tokens) == FAILURE)
			break ;
		while (input[i] && ft_strchr(" \t\n", input[i]))
			i++;
	}
	if (input[i] != '\0')
		return (free_tokens(&tokens), NULL);
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(input);
	if (tokens && tokens[0].type == PIPE)
		return (free_tokens(&tokens), print_error
			("syntax error near unexpected token `newline'"), NULL);
	return (tokens);
}
