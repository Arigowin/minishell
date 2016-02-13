/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 10:45:08 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/13 18:19:24 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_color(char *color, char c)
{
	write(1, color, ft_strlen(color));
	write(1, &c, 1);
	write(1, DEFAULT_COLOR, 6);
}
