/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:09:41 by eakman            #+#    #+#             */
/*   Updated: 2024/05/03 17:08:27 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal;

static int	input_init_requel(t_token **tokens, t_cmd ***cmds)
{
	*tokens = appender(*tokens);
	if (!*tokens)
	{
		update_exit_value(EXIT_SET, 1, 0);
		return (1);
	}
	*cmds = parser(*tokens);
	if (*cmds)
		free_tokens(tokens);
	if (!*cmds)
	{
		update_exit_value(EXIT_SET, 1, 0);
		return (1);
	}
	return (0);
}

static void	input_init(char *input, t_env **env)
{
	t_token	*tokens;
	t_cmd	**cmds;

	g_signal = FT_SIGST;
	tokens = lexer(input);
	if (!tokens)
	{
		update_exit_value(EXIT_SET, 1, 0);
		return ;
	}
	tokens = expander(tokens, *env);
	if (!tokens)
	{
		update_exit_value(EXIT_SET, 1, 0);
		return ;
	}
	if (input_init_requel(&tokens, &cmds))
		return ;
	execute_commands(cmds, env);
	free_cmds(cmds);
}

void	read_input(t_env **env)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			free_env(*env);
			free(env);
			exit(update_exit_value(EXIT_GET, 0, 0));
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		input_init(input, env);
		add_history(input);
		free(input);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_env	**env;
	int		exit_value;

	(void)argv;
	if (argc != 1)
		return (print_error("Please type only one arguments"), 1);
	update_exit_value(EXIT_FIRST, 0, &exit_value);
	env = malloc(sizeof(t_env *));
	if (!env)
		return (print_error(MALLOC_ERR), 1);
	*env = env_init(environ);
	if (!*env)
		return (free(env), 1);
	printf("\033[1;31mMinishell");
	printf("\033[0m by \033[34macosgun\033[0m & \033[33meakman\033[0m\n");
	printf("\n");
	signal_control();
	read_input(env);
	return (0);
}
