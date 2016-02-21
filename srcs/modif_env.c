/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:03 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:03 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_bool	modif_env_2(char ***env, int i, char *str, char *tmp)
{
	ft_strdel(&((*env)[i]));
	if (str != NULL)
	{
		if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
	}
	else
	{
		if (((*env)[i] = ft_strdup(tmp)) == NULL)
			return (ft_error(0, "ERROR : DUP", NULL, FALSE));
	}
	return (TRUE);
}

t_bool	modif_env_3(char ***env, int i, char *name, char *str)
{
	char	*tmp;

	ft_strdel(&((*env)[i]));
	if ((tmp = ft_strjoin(name, "=")) == NULL)
		return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
	if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
		return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
	ft_strdel(&tmp);
	return (TRUE);
}

t_bool	modif_env(char *name, char ***env, char *str)
{
	char	*tmp;
	size_t	i;
	size_t	len;
	size_t	nbenv;
	t_bool	b;

	nbenv = nb_env(*env);
	i = 0;
	b = FALSE;
	while (i < nbenv && !b)
	{
		len = len_to_equal((*env)[i]);
		if ((tmp = ft_strsub((*env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : SUB", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
			b = modif_env_2(env, i, str, tmp);
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
		b = modif_env_3(env, i, name, str);
	return (b);
}
