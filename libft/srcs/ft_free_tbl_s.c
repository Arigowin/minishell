/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tbl_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 17:37:18 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:24:25 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_free_tbl_s(char **tbl)
{
	int		i;

	i = 0;
	while (tbl[i] != NULL)
	{
		free(tbl[i]);
		i++;
	}
	free(tbl);
}
