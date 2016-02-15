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
		}
		else if (ft_strequ(paths[i], "~+"))
		{
			ft_strdel(&paths[i]);
			if ((home = get_env("PWD", s)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error(0, "ERROR : strdup replace tilde", paths[i], FALSE));
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
		}
		i++;
	}
	return (TRUE);
}
