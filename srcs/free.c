/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:02 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:02 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void		ft_freetstring(char ***tab)
{
	size_t		i;

	i = 0;
	if (tab && *tab)
	{
		while ((*tab)[i])
		{
			free((*tab)[i]);
			i++;
		}
		free(*tab);
	}
}
