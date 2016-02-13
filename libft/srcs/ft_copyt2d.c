/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyt2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:14:44 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/13 12:29:59 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_copyt2d(char ***t1, char **t2, size_t size, size_t new_size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	*t1 = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = 0;
	while (i < size)
	{
		(*t1)[i] = ft_strdup(t2[i]);
		i++;
	}
	(*t1)[i] = NULL;
	return (i);
}
