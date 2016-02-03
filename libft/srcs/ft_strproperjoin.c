/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strproperjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:59:58 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/25 16:33:07 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strproperjoin(char **s1, char **s2)
{
	char *tmp;

	tmp = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	*s1 = ft_strdup(tmp);
	ft_strdel(&tmp);
}
