/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 10:29:02 by dolewski          #+#    #+#             */
/*   Updated: 2015/11/28 18:59:32 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_itolet(unsigned int nb)
{
	return (nb + 'A' - 10);
}

static int		ft_puttbl_base(unsigned int n, char *t, char **str, size_t base)
{
	int	i;

	if (n > base - 1)
	{
		t[0] += 1;
		i = ft_puttbl_base(n / base, t, str, base);
	}
	else
	{
		*str = ft_strnew(t[0]);
		i = t[1];
	}
	if (*str != NULL)
	{
		if (base > 10 && (n % base) > 9)
			(*str)[i] = ft_itolet(n % base);
		else
			(*str)[i] = (n % base) + '0';
	}
	return (i + 1);
}

char			*ft_itoa_base(int n, int base)
{
	char	*str;
	char	*t;

	str = NULL;
	t = ft_strnew(2);
	if (base >= 2 && base <= 36)
	{
		if (n < 0)
		{
			t[0] = 1;
			t[1] = 1;
			ft_puttbl_base(-n, t, &str, base);
			if (str != NULL)
				str[0] = '-';
		}
		else
		{
			t[0] = 0;
			t[1] = 0;
			ft_puttbl_base(n, t, &str, base);
		}
	}
	return (str);
}
