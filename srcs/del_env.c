/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:01 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:01 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int		del_env_bis(int i, char ***env, char **tmpenv, char *name)
{
	size_t		len;
	size_t		j;
	char		*tmp;

	j = 0;
	len = len_to_equal((*env)[i]);
	if ((tmp = ft_strsub((*env)[i], 0, len)) == NULL)
		exit(-1);
	if (!(ft_strcmp(tmp, name) == '='))
	{
		if (((*tmpenv) = ft_strdup((*env)[i])) == NULL)
			exit(-1);
		j++;
	}
	ft_strdel(&tmp);
	return (j);
}

t_bool			del_env(char *name, char ***env)
{
	char	**tmpenv;
	size_t	i;
	size_t	j;
	size_t	nbenv;

	nbenv = nb_env(*env);
	i = 0;
	j = 0;
	if ((tmpenv = (char **)malloc(sizeof(char *) * nbenv)) == NULL)
		return (ft_error(2, "ERROR : malloc del_env", NULL, FALSE));
	while ((*env)[i] && (*env)[i][0])
	{
		j += del_env_bis(i, env, &(tmpenv[j]), name);
		i++;
	}
	tmpenv[j] = NULL;
	ft_freetstring(env);
	ft_copyt2d(env, tmpenv, nbenv - 1, nbenv - 1);
	ft_freetstring(&tmpenv);
	return (TRUE);
}
