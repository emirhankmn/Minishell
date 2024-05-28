/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:46:59 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:47:02 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*new_arr;

	i = 0;
	s1_len = ft_strlen((char *) s1);
	s2_len = ft_strlen((char *) s2);
	new_arr = malloc((s1_len + s2_len) * sizeof(char) + 1);
	if (new_arr == 0)
		return (0);
	while (i < s1_len)
	{
		new_arr[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		new_arr[i] = s2[i - s1_len];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}
