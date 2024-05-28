/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:28 by eakman            #+#    #+#             */
/*   Updated: 2024/05/06 14:06:03 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

static void	wait_all(t_cmd **cmds, t_check check)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (!cmds[i + 1])
			waitpid(cmds[i]->p_id, &(check.status), 0);
		else
			waitpid(cmds[i]->p_id, 0, 0);
		i++;
	}
	update_exit_value(EXIT_SET, check.status / 256, 0);
}

static int	multi_restore_files_fd(t_cmd **cmds, t_check check, int ori_fd,
	int ori_fd_in)
{
	int	j;

	j = -1;
	while (cmds[check.i] && cmds[check.i]->output_file
		&& cmds[check.i]->output_file[++j].name)
		close(cmds[check.i]->output_file[j].fd);
	restore_default_fds(ori_fd, ori_fd_in);
	exit (0);
}

static int	ft_child_process(t_cmd **cmds, t_check check,
	int original_fd, int original_fd_in)
{
	close(check.fd[0]);
	if (cmds[check.i + 1])
		dup2(check.fd[1], 1);
	close(check.fd[1]);
	if (execute_builtin(cmds[check.i], check.env, cmds) != INVALID)
		multi_restore_files_fd(cmds, check, original_fd, original_fd_in);
	else if (execute_command(cmds[check.i], *(check.env)) != 127)
		multi_restore_files_fd(cmds, check, original_fd, original_fd_in);
	else
	{
		restore_default_fds(original_fd, original_fd_in);
		print_error_command_not_found(cmds[check.i]->command);
		exit(127);
	}
	return (update_exit_value(EXIT_GET, 0, 0));
}

int	execute_heredocs(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (execute_heredoc(cmds, i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (0);
}

int	execute_multi_command(t_cmd **cmds, t_env **env,
	int original_fd, int original_fd_in)
{
	t_check	check;

	check = init_check();
	check.env = env;
	check.fd_in = dup(0);
	if (pos_last_heredoc(cmds) != -1)
		if (execute_heredocs(cmds) == FAILURE)
			return (FAILURE);
	check.i = pos_last_heredoc(cmds) + 1;
	while (cmds[check.i])
	{
		if (cmds[check.i + 1])
			if (pipe(check.fd) == -1)
				return (print_error("pipe error"), FAILURE);
		cmds[check.i]->p_id = fork();
		if (cmds[check.i]->p_id == 0)
			ft_child_process(cmds, check, original_fd, original_fd_in);
		else if (cmds[check.i]->p_id < 0)
			return (print_error("fork error"), FAILURE);
		dup2(check.fd[0], 0);
		close_pipe(check);
		check.i++;
	}
	dup2(check.fd_in, 0);
	return (close_pipe(check), wait_all(cmds, check), check.status / 256);
}
