/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:14 by eakman            #+#    #+#             */
/*   Updated: 2024/05/03 17:34:08 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

void	print_syntax_error(char *str)
{
	printf("\033[31mminishell:\033[0m");
	printf(" syntax error near unexpected token `%s'\n", str);
}

int	add_flag_and_content(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (check->check_flag && tokens[check->i].content[0] == '-')
	{
		cmds[check->k]->flags_array = \
			add_flag(cmds[check->k]->flags_array, tokens[check->i].content);
		if (!cmds[check->k]->flags_array)
			return (print_error(MALLOC_ERR), free_cmds(cmds),
				free_tokens(&tokens), FAILURE);
	}
	else
	{
		cmds[check->k]->content = \
			add_content(&cmds[check->k]->content,
				ft_strdup(tokens[check->i].content), tokens[check->i].type,
				tokens[check->i].is_append);
		if (!cmds[check->k]->content)
			return (print_error(MALLOC_ERR), free_cmds(cmds),
				free_tokens(&tokens), FAILURE);
		check->check_flag = 0;
	}
	return (1);
}

int	get_cmd_word(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (check->is_command)
	{
		cmds[check->k]->command = ft_strdup(tokens[check->i].content);
		if (!cmds[check->k]->command)
			return (print_error(MALLOC_ERR),
				free_cmds(cmds), free_tokens(&tokens), FAILURE);
		check->is_command = 0;
	}
	else
	{
		if (add_flag_and_content(cmds, tokens, check) == FAILURE)
			return (FAILURE);
	}
	return (1);
}

int	get_cmd_redir_in(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (print_error(
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (tokens[check->i + 1].type == RDR_IN || tokens[check->i + 1].type
		== RDR_OUT || tokens[check->i + 1].type == PIPE)
		return (print_syntax_error(tokens[check->i + 1].content),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (ft_strncmp(tokens[check->i].content, "<<", 3) == 0)
		cmds[check->k]->input_file = \
				add_file(&cmds[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, "<", 2) == 0)
		cmds[check->k]->input_file = \
				add_file(&cmds[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (print_error(
				"syntax error near unexpected token `<'"),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (!cmds[check->k]->input_file)
		return (print_error(MALLOC_ERR), free_cmds(cmds),
			free_tokens(&tokens), FAILURE);
	check->i++;
	return (0);
}

int	get_cmd_redir_out(t_cmd **cmds, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (print_error(
				"syntax error near unexpected token `newline'"),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (tokens[check->i + 1].type == RDR_IN || tokens[check->i + 1].type
		== RDR_OUT || tokens[check->i + 1].type == PIPE)
		return (print_syntax_error(tokens[check->i + 1].content),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (ft_strncmp(tokens[check->i].content, ">>", 3) == 0)
		cmds[check->k]->output_file = \
				add_file(&cmds[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, ">", 2) == 0)
		cmds[check->k]->output_file = \
				add_file(&cmds[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (print_error(
				"syntax error near unexpected token `>'"),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	if (!cmds[check->k]->output_file)
		return (print_error(MALLOC_ERR),
			free_cmds(cmds), free_tokens(&tokens), FAILURE);
	check->i++;
	return (0);
}
