/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:33 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:52:48 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	add_envp(char *envp, t_env **env, int *i)
{
	(*env)[*i].name = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
	if (!(*env)[*i].name)
		return (print_error(MALLOC_ERR), 1);
	(*env)[*i].value = ft_substr(envp, ft_strchr(envp, '=') - envp + 1,
			ft_strlen(envp) - (ft_strchr(envp, '=') - envp + 1));
	if (!(*env)[*i].value)
		return (print_error(MALLOC_ERR), 1);
	(*i)++;
	return (0);
}

static t_env	*get_pwd_env(char *pwdbuf)
{
	t_env	*env;

	env = (t_env *) ft_calloc(sizeof(t_env), 2);
	if (!env)
		return (print_error(MALLOC_ERR), NULL);
	env[0].name = ft_strdup("pwd");
	getcwd(pwdbuf, sizeof(pwdbuf));
	env[0].value = ft_strdup(pwdbuf);
	return (env);
}

t_env	*env_init(char	**envp)
{
	t_env	*env;
	int		i;
	char	pwdbuf[1024];

	i = 0;
	if (!envp || !(*envp))
	{
		env = get_pwd_env(pwdbuf);
		if (!env)
			return (NULL);
		return (env);
	}
	env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen2(envp) + 1);
	if (!env)
		return (print_error(MALLOC_ERR), NULL);
	while (envp[i])
	{
		if (add_envp(envp[i], &env, &i))
			return (NULL);
	}
	update_env(env, "OLDPWD", "");
	return (env);
}
