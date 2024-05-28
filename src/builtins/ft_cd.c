/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:51:23 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:51:26 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	ft_cd_continued(t_cmd *cmd, char *oldpwd)
{
	if (cmd->flags_array && cmd->flags_array[0][0] == '-')
	{
		if (!oldpwd)
		{
			update_exit_value(EXIT_SET, 1, 0);
			return (print_error("OLDPWD not set"));
		}
		if (chdir(oldpwd) == -1)
		{
			update_exit_value(EXIT_SET, 1, 0);
			return (print_error("No such file or directory"));
		}
	}
	else
	{
		if (chdir(cmd->content[0].content) == -1)
		{
			update_exit_value(EXIT_SET, 1, 0);
			return (print_error("No such file or directory"));
		}
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env *env)
{
	char	*oldpwd;
	char	*pwd;
	char	getcwdbuf[1024];

	oldpwd = read_env("OLDPWD", env);
	pwd = read_env("PWD", env);
	if (content_count(cmd) + flag_count(cmd) == 0)
	{
		if (chdir(read_env("HOME", env)) == -1)
			return (update_exit_value(EXIT_SET, 1, 0),
				print_error("HOME not set"));
	}
	else
	{
		if (ft_cd_continued(cmd, oldpwd) == FAILURE)
			return (update_exit_value(EXIT_SET, 1, 0), FAILURE);
	}
	if (update_env(env, "OLDPWD", pwd) == 0)
		return (-1);
	if (update_env(env, "PWD", getcwd(getcwdbuf, sizeof(getcwdbuf))) == 0)
		return (-1);
	return (0);
}
