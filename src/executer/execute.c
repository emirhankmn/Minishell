/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:17 by eakman            #+#    #+#             */
/*   Updated: 2024/05/06 14:04:05 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	execute_heredoc(t_cmd **cmds, int i)
{
	int	j;

	j = -1;
	if (cmds[i]->input_file)
	{
		while (cmds[i]->input_file[++j].name)
		{
			if (cmds[i]->input_file[j].double_op == 1)
			{
				if (heredoc(cmds[i], j) == FAILURE)
				{
					update_exit_value(EXIT_SET, 1, 0);
					return (FAILURE);
				}
			}
		}
	}
	if (g_signal == FT_SIGEXIT)
	{
		update_exit_value(EXIT_SET, 1, 0);
		return (FAILURE);
	}
	return (0);
}

static int	restore_files_fd(t_cmd **cmds, int orig_fd_1, int orig_fd_0)
{
	int	i;

	i = 0;
	while (cmds[0] && cmds[0]->output_file && cmds[0]->output_file[i].name)
	{
		close(cmds[0]->output_file[i].fd);
		i++;
	}
	i = 0;
	while (cmds[0] && cmds[0]->input_file && cmds[0]->input_file[i].name)
	{
		close(cmds[0]->input_file[i].fd);
		i++;
	}
	restore_default_fds(orig_fd_1, orig_fd_0);
	return (0);
}

static int	execute_single_command(t_cmd **cmds, t_env **env)
{
	int	orig_fd_1;
	int	orig_fd_0;

	orig_fd_1 = dup(1);
	orig_fd_0 = dup(0);
	if (execute_heredoc(cmds, 0) == FAILURE)
		return (FAILURE);
	if (execute_builtin(cmds[0], env, cmds) != INVALID)
		return (restore_files_fd(cmds, orig_fd_1, orig_fd_0));
	else if (execute_command(cmds[0], *env) != 127)
	{
		restore_default_fds(orig_fd_1, orig_fd_0);
		return (0);
	}
	else
	{
		restore_default_fds(orig_fd_1, orig_fd_0);
		update_exit_value(EXIT_SET, 127, 0);
		print_error_command_not_found(cmds[0]->command);
		return (FAILURE);
	}
	return (0);
}

int	pos_last_heredoc(t_cmd **cmds)
{
	int	j;
	int	i;
	int	pos;

	j = -1;
	i = -1;
	pos = -1;
	while (cmds[++i])
	{
		if (cmds[i]->input_file)
		{
			while (cmds[i]->input_file[++j].name)
			{
				if (cmds[i]->input_file[j].double_op == 1)
					pos = i;
			}
		}
	}
	return (pos);
}

int	execute_commands(t_cmd **cmds, t_env **env)
{
	int	orig_fd_1;
	int	orig_fd_0;

	g_signal = FT_SIGST;
	if (cmds[0]->command
		&& ft_strncmp(cmds[0]->command, "exit", ft_strlen("exit") + 1) != 0)
		update_exit_value(EXIT_SET, 0, 0);
	if (!cmds)
		return (0);
	orig_fd_1 = dup(1);
	orig_fd_0 = dup(0);
	if (command_counter(cmds) == 1)
	{
		if (execute_single_command(cmds, env) == FAILURE)
			return (FAILURE);
	}
	else
		return (execute_multi_command(cmds, env, orig_fd_1, orig_fd_0));
	return (0);
}
