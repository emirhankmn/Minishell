/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:51:35 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:51:43 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (env && env[i].name)
	{
		if (env[i].value && env[i].value[0] == 0)
		{
			ft_putstr_fd(env[i].name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\n", 1);
		}
		else if (env[i].value && env[i].value[0] != '\0')
		{
			ft_putstr_fd(env[i].name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env[i].value, 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
