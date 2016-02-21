/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:47:59 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:47:59 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	builtins_env(char **t, char ***env)
{
	if (t[1] && t[1][0] == '-' && t[1][1] == 'u')
		return (builtins_unsetenv(t, env));
	else if (t[1] && t[1][0] == '-' && t[1][1] == 'i')
		return (2);
	print_env(*env);
	return (TRUE);
}
