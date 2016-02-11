/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyt2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:14:44 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/11 11:28:36 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_copyt2d(char ***t1, char **t2)
{
	int		i;

	i = 0;
	while (t2[i])
		i++;
	*t1 = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (t2[i])
	{
		(*t1)[i] = ft_strdup(t2[i]);
		i++;
	}
	(*t1)[i] = NULL;
	return (i);
}
