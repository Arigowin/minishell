#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
t_bool	readline(char ***t)
{

#ifdef DEBUG
	ft_putendl("DEBUG : readline");
#endif

	char	*line;
	int		ret;

	if ((ret = get_next_line(0, &line)) != -1)
	{
		if (line && line[0] != '\0')
		{
			if ((*t = lexer(line, SEP)) == NULL)
				return (FALSE);
		}
		else if (line == NULL)
			return (FALSE);
	}
	if (ret == -1)
		return (FALSE);
	return (TRUE);
}

t_bool	replace_tilde(char **paths, t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : replace_tilde");
#endif

	char	**home;
	char	*tmp1;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "~-"))
		{
			ft_strdel(&paths[i]);
			if ((home = get_env("OLDPWD", s)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error(0, "ERROR : strdup replace tilde", paths[i], FALSE));
			ft_freetstring(&home);
		}
		else if (ft_strequ(paths[i], "~+"))
		{
			ft_strdel(&paths[i]);
			if ((home = get_env("PWD", s)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error(0, "ERROR : strdup replace tilde", paths[i], FALSE));
			ft_freetstring(&home);
		}
		else if (paths[i][0] == '~')
		{
			if ((tmp1 = ft_strsub(paths[i], 1, ft_strlen(paths[i]))) == NULL)
				return (ft_error(0, "ERROR : strsub replace_tilde", NULL, FALSE));
			ft_strdel(&paths[i]);
			if ((home = get_env("HOME", s)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strjoin(home[0], tmp1)) == NULL)
				return (ft_error(0, "ERROR : strjoin replace_tilde", NULL, FALSE));
			free(tmp1);
			ft_freetstring(&home);
		}
		i++;
	}
	return (TRUE);
}

t_bool	replace_env_var(char **paths, t_minishell *s)
{
	char	*var;
	char	*start;
	char	*end;
	char	**tmp2;
	t_bool	b;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (paths[i])
	{
		b = TRUE;
		if (ft_strchr(paths[i], '$'))
		{
			j = 0;
			while (paths[i][j] != '\0' && paths[i][j] != '$')
				j++;
			if ((start = ft_strsub(paths[i], 0, j)) == NULL)
				return (ft_error(0, "ERROR : strsub1 replace_env_var", NULL, FALSE));
			k = j;
			while (paths[i][k] != '\0' && paths[i][k] != '/')
				k++;
			if ((var = ft_strsub(paths[i], j + 1, k - j - 1)) == NULL)
				return (ft_error(0, "ERROR : strsub2 replace_env_var", NULL, FALSE));
			if ((end = ft_strsub(paths[i], k, ft_strlen(paths[i]))) == NULL)
				return (ft_error(0, "ERROR : strsub3 replace_env_var", NULL, FALSE));
			tmp2 = get_env(var, s);
			ft_strdel(&(paths[i]));
			if (tmp2 != NULL && tmp2[0] != NULL)
			{
				if ((paths[i] = ft_strjoin(ft_strjoin(start, tmp2[0]), end)) == NULL)
					return (ft_error(0, "ERROR : strjoin1 replace_env_var", NULL, FALSE));
			}
			else
			{
				if ((paths[i] = ft_strjoin(start, end)) == NULL)
					return (ft_error(0, "ERROR : strjoin2 replace_env_var", NULL, FALSE));
			}
		}
		if (ft_strchr(paths[i], '$') == NULL)
			i++;
	}
	return (TRUE);
}
