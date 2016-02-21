/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:04 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:04 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_bool	add_env(char *name, char ***env, char *str)
{
	char	**tmpenv;
	char	*tmp;
	size_t	nbenv;

	nbenv = nb_env(*env);
	ft_copyt2d(&tmpenv, *env, nbenv, nbenv + 1);
	ft_freetstring(env);
	if ((tmp = ft_strjoin(name, "=")) == NULL)
		return (ft_error(0, "ERROR : strjoin add_env", NULL, FALSE));
	if (str != NULL)
	{
		if ((tmpenv[nbenv] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : strjoin add_env", NULL, FALSE));
	}
	else
	{
		if ((tmpenv[nbenv] = ft_strdup(tmp)) == NULL)
			return (ft_error(0, "ERROR : strdup add_env", NULL, FALSE));
	}
	ft_strdel(&tmp);
	tmpenv[nbenv + 1] = NULL;
	ft_copyt2d(env, tmpenv, nbenv + 1, nbenv + 1);
	ft_freetstring(&tmpenv);
	return (TRUE);
}

t_bool	set_env(char *name, char ***env, char *str)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
		{
			return (ft_error(2, "Variable name must contain alphanumeric \
characters.", NULL, TRUE));
		}
		i++;
	}
	if (env_exist(name, *env) == FALSE)
		return (add_env(name, env, str));
	return (modif_env(name, env, str));
}
