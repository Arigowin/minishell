#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

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
		tmp = ft_strsub((s->env)[i], 0, len - 1);
		if (ft_strcmp(tmp, name) == 0)
		{
			b = TRUE;
			ft_strdel(&tmp);
			if ((tmp = ft_strsub((s->env)[i], len, ft_strlen((s->env)[i]))) == NULL)
				b = ft_error(0, "ERROR : sub get_env", (s->env)[i], FALSE);
			if ((ret = ft_strsplit(tmp, ':')) == NULL)
				b = ft_error(0, "ERROR : split get_env", (s->env)[i], FALSE);
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
		tmp = ft_strsub((s->env)[i], 0, len);
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			if (str != NULL)
				(s->env)[i] = ft_strjoin(tmp, str);
			else
				(s->env)[i] = ft_strdup(tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
	{
		tmp = ft_strjoin(name, "=");
		(s->env)[i] = ft_strjoin(tmp, str);
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
	tmpenv = (char **)malloc(sizeof(char *) * s->nbenv);
	while ((s->env)[i] && (s->env)[i][0])
	{
		len = len_to_equal((s->env)[i]);
		tmp = ft_strsub((s->env)[i], 0, len);
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			s->nbenv--;
		}
		else
		{
			tmpenv[j] = ft_strdup((s->env)[i]);
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

	tmpenv = (char **)malloc(sizeof(char *) * (s->nbenv + 1));
	ft_copyt2d(&tmpenv, s->env);
	ft_freet2d(&(s->env), s->nbenv);
	tmp = ft_strjoin(name, "=");
	if (str != NULL)
		tmpenv[s->nbenv] = ft_strjoin(tmp, str);
	else
		tmpenv[s->nbenv] = ft_strdup(tmp);
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
