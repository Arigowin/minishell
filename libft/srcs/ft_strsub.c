/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:04:24 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:21:46 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	new = NULL;
	if (s != NULL)
	{
		new = (char *)malloc(sizeof(char) * (len + 1));
		i = 0;
		if (new != NULL)
		{
			while (i < len && s[start + i])
			{
				new[i] = s[start + i];
				i++;
			}
			new[i] = '\0';
		}
	}
	return (new);
}
