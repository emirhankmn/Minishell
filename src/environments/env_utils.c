/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:29 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:52:31 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	is_env_variable_char(char c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static int	get_exit_value(char **tmp2, char **tmp, char **res)
{
	*tmp2 = ft_itoa(update_exit_value(EXIT_GET, 0, 0));
	if (!tmp2)
		return (free(*res),
			print_error(MALLOC_ERR), FAILURE);
	*tmp = ft_strjoin(*res, *tmp2);
	if (!tmp)
		return (free(*res), free(*tmp2),
			print_error(MALLOC_ERR), FAILURE);
	free(*tmp2);
	return (0);
}

static int	get_dollar_content(t_check check, char **tmp2,
								char **tmp, char **res)
{
	*tmp2 = ft_substr(check.name, check.i + 1, check.j - 1);
	if (!*tmp2)
		return (free(*res),
			print_error(MALLOC_ERR), FAILURE);
	*tmp = ft_strjoin(*res, read_env(*tmp2, *check.env));
	if (!*tmp)
		return (free(*res), free(*tmp2),
			print_error(MALLOC_ERR), FAILURE);
	free(*tmp2);
	return (0);
}

int	expand_dollar(t_check *check, char **res, char **tmp, char **tmp2)
{
	check->j = 1;
	while (check->name[check->i + check->j]
		&& is_env_variable_char(check->name[check->i + check->j]))
		check->j++;
	if (check->name[check->i + check->j - 1] == '$'
		&& check->name [check->i + check->j++] == '?')
	{
		if (get_exit_value(tmp2, tmp, res) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (get_dollar_content(*check, tmp2, tmp, res) == FAILURE)
			return (FAILURE);
	}
	if (!*tmp)
		return (print_error(MALLOC_ERR), FAILURE);
	free(*res);
	*res = *tmp;
	check->i += check->j - 1;
	return (0);
}

char	*expand_env(t_env *env, char *name)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	t_check	check;

	check = init_check();
	check.name = name;
	check.env = &env;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (name[check.i])
	{
		if (name[check.i] != '$')
		{
			res = ft_strjoin_char(res, name[check.i]);
			if (!res)
				return (NULL);
		}
		else
			if (expand_dollar(&check, &res, &tmp, &tmp2) == FAILURE)
				return (NULL);
		check.i++;
	}
	return (res);
}
