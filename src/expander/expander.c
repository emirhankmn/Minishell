/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:39 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:53:41 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	if_end_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

t_token	*expander(t_token *tkns, t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tkns[++i].content)
	{
		if (tkns[i].type == WORD || tkns[i].type == DOUBLE_QUOTE)
		{
			if (!(i > 0 && ft_strncmp(tkns[i - 1].content, "<<", 3) == 0))
			{
				tmp = expand_env(env, tkns[i].content);
				if (!tmp)
					return (print_error(MALLOC_ERR), free_tokens(&tkns), NULL);
				if (if_end_dollar(tkns[i].content) == 1
					&& (tkns[i + 1].is_append == 0))
					tmp = ft_strjoin_char(tmp, '$');
				if (!tmp)
					return (print_error(MALLOC_ERR), free_tokens(&tkns), NULL);
				free(tkns[i].content);
				tkns[i].content = tmp;
			}
		}
	}
	return (tkns);
}
