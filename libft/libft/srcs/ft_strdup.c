/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:49 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:46:50 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char				*ft_strdup(const char *s1)
{
	size_t			i;
	char			*duplicate;
	size_t			str_len;

	i = 0;
	str_len = ft_strlen(s1);
	duplicate = (char*)malloc(str_len + 1);
	if (!duplicate)
		return (NULL);
	while (i < str_len)
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
