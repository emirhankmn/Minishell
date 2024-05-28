/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:52 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:54:54 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>

void	free_contents(t_content **contents)
{
	int	i;

	i = 0;
	while ((*contents)[i].content)
	{
		free((*contents)[i].content);
		i++;
	}
	free(*contents);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->command)
			free(cmds[i]->command);
		if (cmds[i]->flags_array)
			free_double_char(cmds[i]->flags_array);
		if (cmds[i]->content)
			free_contents(&cmds[i]->content);
		if (cmds[i]->input_file)
			free_files(&cmds[i]->input_file);
		if (cmds[i]->output_file)
			free_files(&cmds[i]->output_file);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)[i].content)
	{
		free((*tokens)[i].content);
		i++;
	}
	if (*tokens)
		free(*tokens);
}
