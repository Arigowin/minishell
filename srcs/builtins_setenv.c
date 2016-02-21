/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:00 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_bool			builtins_setenv(char **t, char ***env)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	if (i > 3)
		return (ft_error(2, "Too many arguments.", NULL, TRUE));
	if (t[1] != NULL)
		return (set_env(t[1], env, t[2]));
	else
		print_env(*env);
	return (TRUE);
}
