/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:01 by eakman            #+#    #+#             */
/*   Updated: 2024/05/03 17:10:12 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

int	is_heredoc(t_cmd *cmd)
{
	int	j;

	j = -1;
	if (cmd->input_file)
	{
		while (cmd->input_file[++j].name)
		{
			if (cmd->input_file[j].double_op == 1)
				return (1);
		}
	}
	return (0);
}

static int	execute_fork(t_cmd *cmd, t_check check, t_env *env)
{
	if (!cmd->command && !is_heredoc(cmd))
		exit (1);
	if (!cmd->command && is_heredoc(cmd))
		exit(update_exit_value(EXIT_GET, 0, 0));
	if (access(cmd->command, F_OK) == 0 && access(cmd->command, X_OK) == 0)
	{
		if (execve(cmd->command, check.args_arr, 0) != 0)
			exit(127);
	}
	else if (!is_paths_define(env))
		exit(127);
	else if (execve(check.path, check.args_arr, check.env_arr) != 0)
		exit(127);
	exit(0);
}

static void	free_execute_args(char **args, char *path, char **env_arr)
{
	free_double_char(args);
	free(path);
	free_double_char(env_arr);
}

static int	execute_command_continued(t_cmd *cmd, t_env *env, t_check check)
{
	check.pid = fork();
	if (check.pid < 0)
	{
		free_execute_args(check.args_arr, check.path, check.env_arr);
		return (print_error("fork error"), FAILURE);
	}
	if (check.pid == 0)
	{
		file_duplicate(cmd);
		execute_fork(cmd, check, env);
	}
	if (check.pid > 0 && (check.fd[0] != -1 && check.fd[1] != -1))
	{
		close(check.fd[0]);
		close(check.fd[1]);
	}
	waitpid(check.pid, &check.status, 0);
	update_exit_value(EXIT_SET, check.status / 256, 0);
	return (free_execute_args(check.args_arr, check.path, check.env_arr),
		check.status / 256);
}

int	execute_command(t_cmd *cmd, t_env *env)
{
	t_check	check;
	int		control;

	control = 0;
	check.path = get_command_path(cmd->command, env);
	check.fd[0] = -1;
	check.fd[1] = -1;
	if (!check.path)
		return (print_error(MALLOC_ERR), 0);
	check.args_arr = set_arg_array(cmd);
	if (!check.args_arr)
		return (free(check.path), print_error(MALLOC_ERR), 0);
	check.env_arr = set_env_array(env);
	if (!check.env_arr)
		return (free_double_char(check.args_arr),
			free(check.path), print_error(MALLOC_ERR), 0);
	if (define_input_file(cmd, &control) == 1)
		return (free_execute_args(check.args_arr, check.path, check.env_arr),
			1);
	return (execute_command_continued(cmd, env, check));
}
