/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_pro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:22 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:52:24 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_env	*delete_env(t_env *env, char *name)
{
	t_env	*new_env;
	t_check	check;

	check = init_check();
	check.name = name;
	new_env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen3(env));
	if (!new_env)
		return (print_error(MALLOC_ERR), NULL);
	while (env[check.i].name)
	{
		if (add_old_env_to_new_env_delete(env, new_env, &check))
			return (free_env(new_env), NULL);
	}
	free_env(env);
	return (new_env);
}

t_env	*update_env(t_env *env, char *name, char *value)
{
	int		i;
	char	*old_value;

	i = 0;
	while (env[i].name)
	{
		if (!ft_strncmp(env[i].name, name, ft_strlen(name) + 1))
		{
			old_value = env[i].value;
			env[i].value = ft_strdup(value);
			if (!env[i].value)
				return (env[i].value = old_value,
					print_error(MALLOC_ERR), NULL);
			free(old_value);
			return (env);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 2);
	if (!res)
		return (free(s1), print_error(MALLOC_ERR), NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	free(s1);
	return (res);
}

char	*read_env(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, name, ft_strlen(name) + 1) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

int	is_env_exist(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, name, ft_strlen(name) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}
