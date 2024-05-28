/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:06 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:57:20 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	free_double_char(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	env_counter(t_env *env)
{
	int	i;

	i = 0;
	while (env && env[i].name)
		i++;
	return (i);
}

char	*ft_strjoin_freed(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	**set_env_array(t_env *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = ft_calloc(sizeof(char *), (env_counter(env) + 1));
	if (!env_arr)
		return (NULL);
	while (env && env[i].name)
	{
		env_arr[i] = ft_strdup(env[i].name);
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		env_arr[i] = ft_strjoin_freed(env_arr[i], "=");
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		env_arr[i] = ft_strjoin_freed(env_arr[i], env[i].value);
		if (!env_arr[i])
			return (free_double_char(env_arr), NULL);
		i++;
	}
	env_arr[i] = 0;
	return (env_arr);
}

int	total_command_counter(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->command)
		i++;
	if (cmd->flags_array)
		i += flag_count(cmd);
	if (cmd->content)
		i += content_count(cmd);
	return (i);
}
