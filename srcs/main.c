#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

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

char	**readline()
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

bool	replace_tilde(char **paths, char **env)
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

int		body(char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : body");
#endif

	char	**t;
	char	**paths;
	char	*tmp;
	int		ret_exec;

	if ((t = readline()) == NULL)
		return (TRUE);
	if (ft_strequ(t[0], "exit"))
	{
		ft_putendl("exit");
		return (FALSE);
	}
	if ((paths = get_env("PATH", env)) == NULL)
		return (ft_error("PATH not found ", t[0], TRUE));
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error("command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if (replace_tilde(t, env) == FALSE)
		return (FALSE);
	if ((ret_exec = execprog(tmp, t, NULL)) == -1)
		return (ft_error("exec format error: ", t[0], TRUE));
	return (TRUE);
}

int main(int ac, char **av, char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : START");
#endif

	bool	b;

	if (ac == 1)
	{
		b = TRUE;
		while (b)
		{
			ft_putstr("$> ");
			b = body(env);
		}
	}
	ac = 1;
	(void)av;

#ifdef DEBUG
	ft_putendl("DEBUG : END");
#endif

	return (0);
}
