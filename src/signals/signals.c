/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:41 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 16:07:40 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../../header/minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal == FT_SIGHEREDOC)
		{
			exit(FT_SIGEXIT);
		}
		else
		{
			update_exit_value(EXIT_SET, 1, 0);
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_control(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
