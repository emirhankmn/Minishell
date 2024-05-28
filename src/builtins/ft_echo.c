/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:51:30 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:51:32 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	is_flag_valid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_flag_count(char **flags)
{
	int	i;

	i = 0;
	while (flags && flags[i])
	{
		if (is_flag_valid(flags[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		flag_count;
	char	**flags;

	flags = cmd->flags_array;
	flag_count = valid_flag_count(flags);
	i = flag_count;
	while (flags && flags[i])
	{
		ft_putstr_fd(flags[i], STDOUT_FILENO);
		if (flags[i + 1] || cmd->content)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (cmd->content && cmd->content[i].content)
	{
		ft_putstr_fd(cmd->content[i].content, STDOUT_FILENO);
		if (cmd->content[i + 1].content)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag_count == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
