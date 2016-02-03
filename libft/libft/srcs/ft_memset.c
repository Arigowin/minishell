/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:27 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:46:28 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*save_ptr;

	i = 0;
	save_ptr = b;
	while ((i < len) && (b != NULL))
	{
		*save_ptr = c;
		i++;
		save_ptr++;
	}
	return (b);
}
