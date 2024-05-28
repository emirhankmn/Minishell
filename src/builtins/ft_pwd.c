/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:52:02 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:52:04 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	return (0);
}
