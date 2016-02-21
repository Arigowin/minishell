/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:01 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:01 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_bool	ft_error(int i, char *str, char *exe, t_bool ret)
{
	if (i == 0)
		ft_putstr_fd("minishell: ", 2);
	else if (i == 1)
		ft_putstr_fd("cd: ", 2);
	else if (i == 2)
		ft_putstr_fd("setenv: ", 2);
	else if (i == 3)
		ft_putstr_fd("unsetenv: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(exe, 2);
	return (ret);
}
