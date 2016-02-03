/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:19:18 by dolewski          #+#    #+#             */
/*   Updated: 2015/11/29 11:57:10 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_puttbl(unsigned int n, int len, int sign, char **str)
{
	int	i;

	if (n > 9)
		i = ft_puttbl(n / 10, len + 1, sign, str);
	else
	{
		*str = ft_strnew(len + 1);
		i = sign;
	}
	if (*str != NULL)
		(*str)[i] = (n % 10) + '0';
	return (i + 1);
}

char			*ft_itoa(int n)
{
	char	*str;

	if (n < 0)
	{
		ft_puttbl(-n, 1, 1, &str);
		if (str != NULL)
			str[0] = '-';
	}
	else
		ft_puttbl(n, 0, 0, &str);
	return (str);
}
