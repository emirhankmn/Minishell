/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:57 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:54:58 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	command_counter(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

int	content_count(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->content && cmd->content[i].content)
		i++;
	return (i);
}

int	flag_count(t_cmd *cmd)
{
	int	flag_count;

	flag_count = 0;
	while (cmd->flags_array && cmd->flags_array[flag_count])
		flag_count++;
	return (flag_count);
}
