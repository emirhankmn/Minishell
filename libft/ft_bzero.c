/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:43:07 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:43:11 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*sb;

	if (n == 0)
		return ;
	sb = s;
	i = 0;
	while (i < n)
	{
		sb[i] = 0;
		i++;
	}
}
