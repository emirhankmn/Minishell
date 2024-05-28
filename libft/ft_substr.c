/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:57 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:47:59 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_min(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	nstr_len;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	nstr_len = ft_strlen(s) - start;
	sub_str = malloc((ft_min(nstr_len, len) + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		sub_str[i] = s[i + start];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
