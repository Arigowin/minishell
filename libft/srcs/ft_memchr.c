/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:08 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:46:09 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*save_ptr;

	i = 0;
	save_ptr = s;
	while (i < n)
	{
		if (ft_memcmp(save_ptr, &c, 1) == 0)
			return ((void*)save_ptr);
		i++;
		save_ptr++;
	}
	return (NULL);
}
