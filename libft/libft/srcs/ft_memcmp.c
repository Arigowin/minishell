/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:13 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:06:47 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*save_ptr;
	const unsigned char	*save_ptr_2;

	save_ptr = s1;
	save_ptr_2 = s2;
	if (n == 0 || (s1 == NULL && s2 == NULL))
		return (0);
	while (n--)
	{
		if (*save_ptr != *save_ptr_2)
			return (*save_ptr - *save_ptr_2);
		save_ptr++;
		save_ptr_2++;
	}
	return (0);
}
