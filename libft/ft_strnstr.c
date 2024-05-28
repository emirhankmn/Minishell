/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:39 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:47:42 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0
			&& i + ft_strlen(needle) <= len)
			return ((char *) &haystack[i]);
		i++;
	}
	return (0);
}
