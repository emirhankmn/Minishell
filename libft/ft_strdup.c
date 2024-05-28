/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:46:45 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:46:48 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*new_arr;
	size_t	arr_len;
	size_t	i;

	arr_len = ft_strlen(s1);
	new_arr = (char *) malloc((arr_len + 1) * sizeof(char));
	if (new_arr == 0)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = s1[i];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}
