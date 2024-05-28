/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <eakman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:44 by eakman            #+#    #+#             */
/*   Updated: 2024/04/29 13:47:46 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*lastpos;
	int		i;

	lastpos = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			lastpos = (char *)&s[i];
		i++;
	}
	if ((char) c == s[i])
		return ((char *)&s[i]);
	return (lastpos);
}
