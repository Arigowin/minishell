/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyt2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:14:44 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/12 17:18:44 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_copyt2d(char ***t1, char **t2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (t2[len])
		len++;
	*t1 = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		(*t1)[i] = ft_strdup(t2[i]);
		i++;
	}
	(*t1)[i] = NULL;
	return (i);
}
