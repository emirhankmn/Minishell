/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:39 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:45:42 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1char;
	unsigned char	*s2char;

	if (n == 0)
		return (0);
	s1char = (unsigned char *) s1;
	s2char = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1char[i] != s2char[i])
			return (s1char[i] - s2char[i]);
		i++;
	}
	return (0);
}
