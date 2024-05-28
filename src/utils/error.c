/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:48 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:54:50 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	print_error_command_not_found(char *command)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (FAILURE);
}

int	print_error(char *error_type)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}
