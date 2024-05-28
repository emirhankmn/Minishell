/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:06 by eakman            #+#    #+#             */
/*   Updated: 2024/05/03 12:00:04 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <fcntl.h>

int	is_a_path(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_paths_define(t_env *env)
{
	if (read_env("PATH", env))
		return (1);
	return (0);
}

void	file_duplicate(t_cmd *cmd)
{
	int	i;

	if (cmd->output_file)
	{
		i = 0;
		while (cmd->output_file[i].name)
		{
			dup2(cmd->output_file[i].fd, 1);
			i++;
		}
	}
	if (cmd->input_file)
	{
		i = 0;
		while (cmd->input_file[i].name)
		{
			dup2(cmd->input_file[i].fd, 0);
			i++;
		}
	}
}

static int	define_output_file(t_cmd *cmd, int *control)
{
	int	i;

	i = 0;
	while (cmd->output_file && cmd->output_file[i].name)
	{
		if (cmd->output_file[i].double_op == 1)
		{
			cmd->output_file[i].fd = open(cmd->output_file[i].name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (cmd->output_file[i].double_op == 0)
		{
			cmd->output_file[i].fd = open(cmd->output_file[i].name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (cmd->output_file[i].fd == -1)
		{
			print_error("permission denied");
			update_exit_value(EXIT_SET, 1, 0);
			*control = 1;
			return (FAILURE);
		}
		i++;
	}
	return (0);
}

int	define_input_file(t_cmd *cmd, int *control)
{
	int	i;

	i = 0;
	if (define_output_file(cmd, control) == FAILURE)
		return (1);
	while (cmd->input_file && cmd->input_file[i].name)
	{
		if (cmd->input_file[i].double_op == 0)
		{
			cmd->input_file[i].fd = open(cmd->input_file[i].name,
					O_RDONLY, 0644);
		}
		if (cmd->input_file[i].fd == -1 && cmd->input_file[i].double_op == 0)
		{
			if (access(cmd->input_file[i].name, F_OK) == 0)
				print_error("permission denied");
			else
				print_error("No such file or directory");
			update_exit_value(EXIT_SET, 1, 0);
			*control = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
