#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
size_t		len_to_equal(char *str)
{

#ifdef DEBUG
	ft_putendl("DEBUG : len_to_equal");
#endif

	size_t	i;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '=')
		i++;
	return (i + 1);
}

char	**get_env(char *name, t_minishell *s)
{

#ifdef DEBUG
	ft_putstr("DEBUG : get_env : ");
	ft_putendl(name);
#endif

	char	**ret;
	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;

	i = 0;
	ret = NULL;
	b = FALSE;
	while (i < s->nbenv)
	{
		len = len_to_equal((s->env)[i]);
		if ((tmp = ft_strsub((s->env)[i], 0, len - 1)) == NULL)
			return (NULL);
		if (ft_strcmp(tmp, name) == 0)
		{
			b = TRUE;
			ft_strdel(&tmp);
			if ((tmp = ft_strsub((s->env)[i], len, ft_strlen((s->env)[i]))) == NULL)
				b = ft_error(0, "ERROR : strsub get_env", (s->env)[i], FALSE);
			if ((ret = ft_strsplit(tmp, ':')) == NULL)
				b = ft_error(0, "ERROR : strsplit get_env", (s->env)[i], FALSE);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	if (b == FALSE)
		return (NULL);
	ft_strdel(&tmp);
	return (ret);
}

t_bool	modif_env(char *name, t_minishell *s, char *str)
{

#ifdef DEBUG
	ft_putstr("DEBUG : modif_env : ");
	ft_putendl(name);
#endif

	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;

	i = 0;
	b = FALSE;
	while (i < s->nbenv && !b)
	{
		len = len_to_equal((s->env)[i]);
		if ((tmp = ft_strsub((s->env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : strsub modif_env", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			if (str != NULL)
			{
				if (((s->env)[i] = ft_strjoin(tmp, str)) == NULL)
					return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
			}
			else
			{
				if (((s->env)[i] = ft_strdup(tmp)) == NULL)
					return (ft_error(0, "ERROR : strdup modif_env", NULL, FALSE));
			}
		}
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
	{
		if ((tmp = ft_strjoin(name, "=")) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		if (((s->env)[i] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		b = TRUE;
	}
	i = 0;
	return (b);
}

t_bool	del_env(char *name, t_minishell *s)
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

	i = 0;
	j = 0;
	b = FALSE;
	if ((tmpenv = (char **)malloc(sizeof(char *) * s->nbenv)) == NULL)
		return (ft_error(2, "ERROR : malloc del_env", NULL, FALSE));
	while ((s->env)[i] && (s->env)[i][0])
	{
		len = len_to_equal((s->env)[i]);
		if ((tmp = ft_strsub((s->env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : strsub del_env", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			s->nbenv--;
		}
		else
		{
			if ((tmpenv[j] = ft_strdup((s->env)[i])) == NULL)
				return (ft_error(0, "ERROR : strdup del_env", NULL, FALSE));
			j++;
		}
		i++;
	}
	tmpenv[j] = NULL;
	ft_freet2d(&(s->env), s->nbenv + 1);
	ft_copyt2d(&(s->env), tmpenv);
	ft_freet2d(&tmpenv, s->nbenv);
	return (b);
}

t_bool	add_env(char *name, t_minishell *s, char *str)
{

#ifdef DEBUG
	ft_putstr("DEBUG : add_env : ");
	ft_putendl(name);
#endif

	char	**tmpenv;
	char	*tmp;

//	if ((tmpenv = (char **)malloc(sizeof(char *) * (s->nbenv + 1))) == NULL)
//		return (ft_error(2, "ERROR : malloc add_env", NULL, FALSE));

	ft_copyt2d(&tmpenv, s->env);
	ft_freet2d(&(s->env), s->nbenv);
	if ((tmp = ft_strjoin(name, "=")) == NULL)
		return (ft_error(0, "ERROR : strjoin add_env", NULL, FALSE));
	if (str != NULL)
	{
		if ((tmpenv[s->nbenv] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : strjoin add_env", NULL, FALSE));
	}
	else
	{
		if ((tmpenv[s->nbenv] = ft_strdup(tmp)) == NULL)
			return (ft_error(0, "ERROR : strdup add_env", NULL, FALSE));
	}
	ft_strdel(&tmp);
	s->nbenv++;
	tmpenv[s->nbenv] = NULL;
	ft_copyt2d(&(s->env), tmpenv);
	ft_freet2d(&tmpenv, s->nbenv);

	return (TRUE);
}

t_bool	set_env(char *name, t_minishell *s, char *str)
{

#ifdef DEBUG
	ft_putstr("DEBUG : set_env : ");
	ft_putendl(name);
#endif

	size_t	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (ft_error(2, "Variable name must contain alphanumeric characters.", NULL, TRUE));
		i++;
	}
	if (get_env(name, s) == NULL)
		return (add_env(name, s, str));
	return (modif_env(name, s, str));
}

void	print_env(t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : print_env");
#endif

	size_t	i;

	i = 0;
	while (i < s->nbenv)
	{
		ft_putendl((s->env)[i]);
		i++;
	}
}
