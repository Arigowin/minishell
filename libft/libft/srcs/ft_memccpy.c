/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:46:03 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:46:05 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char		*save_ptr;
	char		*save_ptr_2;

	save_ptr = (char*)s1;
	save_ptr_2 = (char*)s2;
	while (n > 0)
	{
		*save_ptr = *save_ptr_2;
		save_ptr++;
		if (*save_ptr_2 == c)
			return (save_ptr);
		save_ptr_2++;
		n--;
	}
	return (NULL);
}
