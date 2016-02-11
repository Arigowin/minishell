#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

#include <stdio.h>
void	ft_tab_to_space(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\t')
			(*str)[i] = ' ';
		i++;
	}
}

char	**readline(void)
{

#ifdef DEBUG
	ft_putendl("DEBUG : readline");
#endif

	char	*line;
	char	*tmp;

	if (get_next_line(0, &line) != -1 && line[0] != '\0')
	{
		if ((tmp = ft_strtrim(line)) == NULL)
			return (NULL);
		ft_tab_to_space(&tmp);
		ft_strdel(&line);
		return (ft_strsplit(tmp, ' '));
	}
	return (NULL);
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
			home = get_env("OLDPWD", s);
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error(0, "strdup replace tilde", paths[i], FALSE));
		}
		else if (ft_strequ(paths[i], "~+"))
		{
			ft_strdel(&paths[i]);
			home = get_env("PWD", s);
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error(0, "strdup replace tilde", paths[i], FALSE));
		}
		else if (paths[i][0] == '~')
		{
			if ((tmp1 = ft_strsub(paths[i], 1, ft_strlen(paths[i]))) == NULL)
				return (ft_error(0, "ERROR : strsub replace_tilde", NULL, FALSE));
			ft_strdel(&paths[i]);
			home = get_env("HOME", s);
			if ((paths[i] = ft_strjoin(home[0], tmp1)) == NULL)
				return (ft_error(0, "ERROR : strjoin replace_tilde", NULL, FALSE));
		}
		i++;
	}
	return (TRUE);
}
