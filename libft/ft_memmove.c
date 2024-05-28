/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:57 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:45:59 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dstch;
	unsigned char	*srcch;

	if (dst == src || !len)
		return (dst);
	else if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		i = len;
		dstch = (unsigned char *) dst;
		srcch = (unsigned char *) src;
		while (i > 0)
		{
			dstch[i - 1] = srcch[i - 1];
			i--;
		}
	}
	return (dst);
}
