/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:32 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:45:36 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sc;
	size_t			i;

	sc = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (sc[i] == (unsigned char) c)
			return (&(sc[i]));
		i++;
	}
	return (0);
}
