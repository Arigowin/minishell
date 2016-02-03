/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:45:16 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:45:19 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*save_ptr;

	i = 0;
	save_ptr = s;
	while (i < n)
	{
		*save_ptr = '\0';
		i++;
		save_ptr++;
	}
}
