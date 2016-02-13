/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:45:12 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/13 18:18:55 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_color(char *color, char *s)
{
	write(1, color, ft_strlen(color));
	write(1, s, ft_strlen(s));
	write(1, DEFAULT_COLOR, 6);
}
