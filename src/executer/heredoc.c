/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:23 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 17:40:31 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	heredoc_requel(t_cmd *cmd, int *fd, int i)
{
	char	*line;

	close(fd[0]);
	g_signal = FT_SIGHEREDOC;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, cmd->input_file[i].name,
				ft_strlen(cmd->input_file[i].name) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
}

int	heredoc(t_cmd *cmd, int i)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (print_error("pipe error"), FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (g_signal == FT_SIGEXIT)
			exit (FT_SIGEXIT);
		heredoc_requel(cmd, fd, i);
		exit(0);
	}
	else if (pid < 0)
		return (print_error("fork error"), FAILURE);
	else
	{
		waitpid(pid, &status, 0);
		g_signal = status / 256;
		close(fd[1]);
		cmd->input_file[0].fd = fd[0];
	}
	return (0);
}
