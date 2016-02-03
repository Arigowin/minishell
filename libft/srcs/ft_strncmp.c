/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:47:16 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:47:17 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int							ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char		*s_one;
	const unsigned char		*s_two;

	if (n == 0)
		return (0);
	s_one = (const unsigned char*)s1;
	s_two = (const unsigned char*)s2;
	while (*s_one != '\0' && n > 1 && *s_one == *s_two)
	{
		s_one++;
		s_two++;
		n--;
	}
	return (*s_one - *s_two);
}
