/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:31 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:54:35 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

char	*get_command_path_continued(char **paths, int i, char *command)
{
	char	*path;

	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (free_double_char(paths), NULL);
		path = ft_strjoin_freed(path, command);
		if (!path)
			return (free_double_char(paths), NULL);
		if (access(path, F_OK) == 0)
			return (free_double_char(paths), path);
		free (path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *command, t_env *env)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, "PATH", ft_strlen("PATH") + 1) == 0)
			break ;
		i++;
	}
	if (!is_env_exist("PATH", env))
		return (ft_strdup(""));
	paths = ft_split(env[i].value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	path = get_command_path_continued(paths, i, command);
	if (path)
		return (path);
	return (free_double_char(paths), ft_strdup(command));
}
