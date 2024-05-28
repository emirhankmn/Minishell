/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:51:53 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:51:55 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	ft_only_export(t_env *env)
{
	int	i;

	i = 0;
	while (env && env[i].name)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i].name, 1);
		if (env[i].value && env[i].value[0] == '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd("\"", 1);
		}
		if (env[i].value && env[i].value[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env[i].value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	is_valid_env_var_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_content_len(t_content *content)
{
	int	i;

	i = 0;
	while (content && content[i].content)
		i++;
	return (i);
}
