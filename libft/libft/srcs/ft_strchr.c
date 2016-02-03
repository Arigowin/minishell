/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:08:13 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:21:08 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	if (s1)
	{
		while (s1[i] != '\0')
		{
			if (s1[i] == (char)c)
				return (s1 + i);
			i++;
		}
		if (s1[i] == (char)c)
			return (s1 + i);
	}
	return (NULL);
}
