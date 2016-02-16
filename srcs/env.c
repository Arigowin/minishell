#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
size_t		len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '=')
		i++;
	return (i + 1);
}

size_t	nb_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

t_bool	env_exist(char *name, char **env)
{
	t_bool	b;
	size_t	i;
	size_t	len;
	size_t	nbenv;
	char	*tmp;

	nbenv = nb_env(env);
	b = FALSE;
	i = 0;
	while (!b && i < nbenv)
	{
		len = len_to_equal(env[i]);
		if ((tmp = ft_strsub(env[i], 0, len - 1)) == NULL)
			return (FALSE);
		if (ft_strcmp(tmp, name) == 0)
			b = TRUE;
		ft_strdel(&tmp);
		i++;
	}
	return (b);
}

char	*get_env(char *name, char **env)
{

#ifdef DEBUG
	ft_putstr("DEBUG : get_env : ");
	ft_putendl(name);
#endif

	char	*ret;
	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(env);
	i = 0;
	ret = NULL;
	b = FALSE;
	while (i < nbenv)
	{
		len = len_to_equal(env[i]);
		if ((tmp = ft_strsub(env[i], 0, len - 1)) == NULL)
			return (NULL);
		if (ft_strcmp(tmp, name) == 0)
		{
			b = TRUE;
			if ((ret = ft_strsub(env[i], len, ft_strlen(env[i]))) == NULL)
				b = ft_error(0, "ERROR : strsub get_env", env[i], FALSE);
			i = nbenv;
		}
		ft_strdel(&tmp);
		i++;
	}
	if (b == FALSE)
		return (NULL);
	return (ret);
}

t_bool	modif_env(char *name, char ***env, char *str)
{

#ifdef DEBUG
	ft_putstr("DEBUG : modif_env : ");
	ft_putendl(name);
#endif

	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(*env);
	i = 0;
	b = FALSE;
	while (i < nbenv && !b)
	{
		len = len_to_equal((*env)[i]);
		if ((tmp = ft_strsub((*env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : strsub modif_env", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
		{
			ft_strdel(&((*env)[i]));
			b = TRUE;
			if (str != NULL)
			{
				if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
					return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
			}
			else
			{
				if (((*env)[i] = ft_strdup(tmp)) == NULL)
					return (ft_error(0, "ERROR : strdup modif_env", NULL, FALSE));
			}
		}
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
	{
		ft_strdel(&((*env)[i]));
		if ((tmp = ft_strjoin(name, "=")) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		ft_strdel(&tmp);
		b = TRUE;
	}
	i = 0;
	return (b);
}

t_bool	del_env(char *name, char ***env)
{

#ifdef DEBUG
	ft_putstr("DEBUG : del_env : ");
	ft_putendl(name);
#endif

	char	*tmp;
	char	**tmpenv;
	size_t	i;
	size_t	j;
	int		len;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(*env);
	i = 0;
	j = 0;
	b = FALSE;
	if ((tmpenv = (char **)malloc(sizeof(char *) * nbenv)) == NULL)
		return (ft_error(2, "ERROR : malloc del_env", NULL, FALSE));
	while ((*env)[i] && (*env)[i][0])
	{
		len = len_to_equal((*env)[i]);
		if ((tmp = ft_strsub((*env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : strsub del_env", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
			b = TRUE;
		else
		{
			if ((tmpenv[j] = ft_strdup((*env)[i])) == NULL)
				return (ft_error(0, "ERROR : strdup del_env", NULL, FALSE));
			j++;
		}
		ft_strdel(&tmp);
		i++;
	}
	tmpenv[j] = NULL;
	ft_freetstring(env);
	ft_copyt2d(env, tmpenv, nbenv - 1, nbenv - 1);
	ft_freetstring(&tmpenv);
	return (b);
}

t_bool	add_env(char *name, char ***env, char *str)
{

#ifdef DEBUG
	ft_putstr("DEBUG : add_env : ");
	ft_putendl(name);
#endif

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

#ifdef DEBUG
	ft_putstr("DEBUG : set_env : ");
	ft_putendl(name);
#endif

	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (ft_error(2, "Variable name must contain alphanumeric characters.", NULL, TRUE));
		i++;
	}
	if ((tmp = get_env(name, *env)) == NULL)
	{
		free(tmp);
		return (add_env(name, env, str));
	}
	free(tmp);
	return (modif_env(name, env, str));
}

void	print_env(char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : print_env");
#endif

	size_t	i;
	size_t	nb;

	i = 0;
	nb = nb_env(env);
	while (i < nb)
	{
		ft_putendl(env[i]);
		i++;
	}
}
