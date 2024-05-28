/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:54:10 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:54:12 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

char	**add_flag(char **flags, char *flag)
{
	char	**new_flags;
	int		i;

	i = 0;
	while (flags && flags[i])
		i++;
	new_flags = malloc(sizeof(char *) * (i + 2));
	if (!new_flags)
		return (NULL);
	i = 0;
	while (flags && flags[i])
	{
		new_flags[i] = flags[i];
		i++;
	}
	new_flags[i] = ft_strdup(flag);
	if (!new_flags[i])
	{
		free(new_flags);
		return (NULL);
	}
	new_flags[i + 1] = NULL;
	if (flags)
		free(flags);
	return (new_flags);
}
