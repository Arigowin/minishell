/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 18:47:53 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/09 18:47:54 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*save_ptr;

	save_ptr = (char*)s;
	while (*save_ptr != '\0')
		save_ptr++;
	while ((save_ptr != s) && (*save_ptr != c))
		save_ptr--;
	if ((save_ptr == s) && (*s != c))
		return (NULL);
	return (save_ptr);
}
