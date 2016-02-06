#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

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

t_bool	replace_tilde(char **paths, char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : replace_tilde");
#endif

	char	**home;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "~-"))
		{
			ft_strdel(&paths[i]);
			home = get_env("OLDPWD", env);
			if ((paths[i] = ft_strnew(ft_strlen(home[0]))) == NULL)
				return (ft_error("strnew replace_tilde", paths[i], FALSE));
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error("strdup replace tilde", paths[i], FALSE));
		}
		else if (ft_strequ(paths[i], "~+"))
		{
			ft_strdel(&paths[i]);
			home = get_env("PWD", env);
			if ((paths[i] = ft_strnew(ft_strlen(home[0]))) == NULL)
				return (ft_error("strnew replace_tilde", paths[i], FALSE));
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error("strdup replace tilde", paths[i], FALSE));
		}
		else if (ft_strequ(paths[i], "~"))
		{
			ft_strdel(&paths[i]);
			home = get_env("HOME", env);
			if ((paths[i] = ft_strnew(ft_strlen(home[0]))) == NULL)
				return (ft_error("strnew replace_tilde", paths[i], FALSE));
			if ((paths[i] = ft_strdup(home[0])) == NULL)
				return (ft_error("strdup replace tilde", paths[i], FALSE));
		}
		i++;
	}
	return (TRUE);
}
