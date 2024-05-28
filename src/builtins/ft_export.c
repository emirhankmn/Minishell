/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:51:58 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:52:00 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	_get_envs(t_cmd *cmd, t_env *env, int i)
{
	env[i].name = ft_strndup(cmd->content[i].content,
			ft_strchr(cmd->content[i].content, '=') - cmd->content[i].content);
	if (!env[i].name)
		return (free_env(env), FAILURE);
	env[i].value = ft_strdup(ft_strchr(cmd->content[i].content, '=') + 1);
	if (!env[i].value)
		return (free_env(env), FAILURE);
	return (0);
}

static t_env	*get_new_env_vars(t_cmd *cmd)
{
	int		i;
	t_env	*env;

	i = 0;
	env = ft_calloc(sizeof(t_env), (export_content_len(cmd->content) + 1));
	if (!env)
		return (NULL);
	while (cmd->content && cmd->content[i].content)
	{
		if (ft_strchr(cmd->content[i].content, '='))
		{
			if (_get_envs(cmd, env, i) == FAILURE)
				return (NULL);
		}
		else
		{
			env[i].name = ft_strdup(cmd->content[i].content);
			if (!env[i].name)
				return (free_env(env), NULL);
			env[i].value = NULL;
		}
		i++;
	}
	env[i].name = NULL;
	return (env[i].value = NULL, env);
}

static void	ft_export_continued(t_env **env, t_env *new_envs, int i)
{
	if (new_envs[i].name[0] == '\0'
		|| (is_valid_env_var_name(new_envs[i].name) == 0))
	{
		update_exit_value(EXIT_SET, 1, 0);
		print_error("not a valid identifier");
	}
	else
	{
		if (is_env_exist(new_envs[i].name, *env))
		{
			if (new_envs[i].value)
				update_env(*env, new_envs[i].name, new_envs[i].value);
			else
				update_env(*env, new_envs[i].name, 0);
		}
		else
		{
			if (new_envs[i].value)
				*env = add_env(*env, new_envs[i].name, new_envs[i].value);
			else
				*env = add_env(*env, new_envs[i].name, 0);
		}
	}
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	t_env	*new_envs;
	int		i;

	i = 0;
	if (!cmd->content || !cmd->content[0].content)
	{
		ft_only_export(*env);
		return (0);
	}
	else
	{
		new_envs = get_new_env_vars(cmd);
		if (!new_envs)
			return (print_error(MALLOC_ERR), 0);
		while (new_envs[i].name)
		{
			ft_export_continued(env, new_envs, i);
			i++;
		}
	}
	return (free_env(new_envs), 0);
}
