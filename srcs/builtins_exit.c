/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:00 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	b_exit2(char **t)
{
	size_t		i;

	i = 0;
	while (t[1][i])
	{
		if (!ft_isdigit(t[1][i]))
		{
			ft_putstr("exit: ");
			ft_putstr(t[1]);
			ft_putendl(": numeric argument required");
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(t[1]));
}

t_bool			builtins_exit(char **t, char ***env)
{
	if (t[1] != NULL && t[2] == NULL)
	{
		ft_putendl("exit");
		ft_freetstring(env);
	}
	if (t[1] != NULL && t[2] == NULL)
		b_exit2(t);
	else if (t[1] != NULL && t[2] != NULL)
	{
		ft_putendl("exit: Expression Syntax.");
		return (TRUE);
	}
	else
		exit(0);
	return (FALSE);
}
