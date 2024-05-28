/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:26 by eakman            #+#    #+#             */
/*   Updated: 2024/05/03 17:33:32 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	reset_check(t_check *check)
{
	check->is_command = 1;
	check->check_flag = 1;
	check->j++;
	check->i++;
}

static int	get_cmd(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (tokens[check->i].type == WORD || tokens[check->i].type == SINGLE_QUOTE
		|| tokens[check->i].type == DOUBLE_QUOTE)
		return (get_cmd_word(cmds, tokens, check));
	else if (tokens[check->i].type == RDR_IN)
		return (get_cmd_redir_in(cmds, tokens, check));
	else if (tokens[check->i].type == RDR_OUT)
		return (get_cmd_redir_out(cmds, tokens, check));
	return (1);
}

static int	parser_requel(t_token *tokens, t_cmd **cmds, t_check *check)
{
	while (tokens[check->i].content)
	{
		if (tokens[check->i].type == PIPE)
		{
			if (tokens[check->i + 1].type == PIPE)
			{
				if (tokens[check->i + 1].is_append == 0)
					print_error("syntax error near unexpected token `|'");
				else if (tokens[check->i + 1].is_append == 1)
					print_error("'||' is not allowed");
				free_cmds(cmds);
				free_tokens(&tokens);
				return (1);
			}
			reset_check(check);
			break ;
		}
		if (get_cmd(cmds, tokens, check) == FAILURE)
			return (1);
		check->i++;
	}
	return (0);
}

t_cmd	**parser(t_token *tokens)
{
	t_cmd	**cmds;
	t_check	check;

	check = init_check();
	cmds = init_cmd(tokens, check);
	if (!cmds)
		return (free_tokens(&tokens), NULL);
	while (check.k < pipe_counter(tokens) + 1)
	{
		if (!tokens[check.i].content)
		{
			print_error("syntax error: incomplete pipe");
			free_cmds(cmds);
			free_tokens(&tokens);
			return (NULL);
		}
		if (parser_requel(tokens, cmds, &check))
			return (NULL);
		check.k++;
	}
	return (cmds);
}
