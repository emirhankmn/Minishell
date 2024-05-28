/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:12 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:53:14 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	restore_default_fds(int original_fd, int original_fd_in)
{
	dup2(original_fd, 1);
	dup2(original_fd_in, 0);
	close(original_fd);
	close(original_fd_in);
}
