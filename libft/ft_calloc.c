/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:43:27 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:43:29 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	mem = malloc(count * size);
	if (mem == 0)
		return (0);
	i = 0;
	while (i < count * size)
	{
		mem[i] = 0;
		i++;
	}
	return ((void *) mem);
}
