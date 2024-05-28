/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:46:02 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:46:04 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bn;

	bn = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		bn[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
