/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:50 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:45:53 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstchar;
	unsigned char	*srcchar;

	dstchar = (unsigned char *) dst;
	srcchar = (unsigned char *) src;
	i = 0;
	if (dstchar == srcchar || !n)
		return (dst);
	while (i < n)
	{
		dstchar[i] = srcchar[i];
		i++;
	}
	return (dst);
}
