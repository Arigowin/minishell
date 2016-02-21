/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unsetenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:00 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool			builtins_unsetenv(char **t, char ***env)
{
	int		i;

	i = 0;
	while (t[i])
	{
		if (env_exist(t[i], *env))
			del_env(t[i], env);
		i++;
	}
	return (TRUE);
}
