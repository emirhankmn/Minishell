/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:23 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:47:25 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*n_str;
	unsigned int		i;

	i = 0;
	n_str = ft_strdup(s);
	if (!n_str)
		return (0);
	while (s[i])
	{
		n_str[i] = f(i, s[i]);
		i++;
	}
	return (n_str);
}
