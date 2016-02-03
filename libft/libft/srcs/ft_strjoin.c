/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:18:23 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:48:57 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*n;

	i = -1;
	j = 0;
	n = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		n = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (n != NULL)
		{
			while (s1[++i])
				n[i] = s1[i];
			while (s2[j])
			{
				n[i + j] = s2[j];
				j++;
			}
			n[i + j] = '\0';
		}
	}
	return (n);
}
