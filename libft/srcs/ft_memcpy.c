/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:17 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:07:52 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*save_ptr;
	const char	*save_ptr_2;

	i = 0;
	if (n == 0 || s1 == s2)
		return (s1);
	save_ptr = s1;
	save_ptr_2 = s2;
	while (i < n)
	{
		*save_ptr = *save_ptr_2;
		save_ptr++;
		save_ptr_2++;
		i++;
	}
	return (s1);
}
