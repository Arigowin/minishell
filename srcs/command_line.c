#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"
#include <stdlib.h>

t_bool	readline(char ***t)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(0, &line)) != -1)
	{
		if (line && line[0] != '\0')
		{
			if ((*t = lexer(line, SEP)) == NULL)
				return (FALSE);
			ft_strdel(&line);
		}
		else if (line == NULL)
			return (FALSE);
	}
	if (ret == -1)
		return (FALSE);
	return (TRUE);
}

t_bool	replace_tilde(char **paths, char **env)
{
	char	*home;
	char	*tmp1;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "~-"))
		{
			ft_strdel(&paths[i]);
			if ((home = get_env("OLDPWD", env)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strdup(home)) == NULL)
				return (ft_error(0, "ERROR : strdup replace tilde", paths[i], FALSE));
			free(home);
		}
		else if (ft_strequ(paths[i], "~+"))
		{
			ft_strdel(&paths[i]);
			if ((home = get_env("PWD", env)) == NULL)
					return (TRUE);
			if ((paths[i] = ft_strdup(home)) == NULL)
				return (ft_error(0, "ERROR : strdup replace tilde", paths[i], FALSE));
			free(home);
		}
		else if (paths[i][0] == '~')
		{
			if ((tmp1 = ft_strsub(paths[i], 1, ft_strlen(paths[i]))) == NULL)
				return (ft_error(0, "ERROR : strsub replace_tilde", NULL, FALSE));
			ft_strdel(&paths[i]);
			if ((home = get_env("HOME", env)) == NULL)
			{
				free(tmp1);
				return (TRUE);
			}
			if ((paths[i] = ft_strjoin(home, tmp1)) == NULL)
				return (ft_error(0, "ERROR : strjoin replace_tilde", NULL, FALSE));
			free(tmp1);
			free(home);
		}
		i++;
	}
	return (TRUE);
}

t_bool	replace_env_var(char **cmd, char **env)
{
	char	*var;
	char	*start;
	char	*end;
	char	*tmp2;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			j = 0;
			while (cmd[i][j] != '\0' && cmd[i][j] != '$')
				j++;
			if ((start = ft_strsub(cmd[i], 0, j)) == NULL)
				return (ft_error(0, "ERROR : strsub1 replace_env_var", NULL, FALSE));
			k = j;
			while (cmd[i][k] != '\0' && cmd[i][k] != '/')
				k++;
			if ((var = ft_strsub(cmd[i], j + 1, k - j - 1)) == NULL)
				return (ft_error(0, "ERROR : strsub2 replace_env_var", NULL, FALSE));
			if ((end = ft_strsub(cmd[i], k, ft_strlen(cmd[i]))) == NULL)
				return (ft_error(0, "ERROR : strsub3 replace_env_var", NULL, FALSE));
			tmp2 = get_env(var, env);
			free(cmd[i]);
			if (tmp2 != NULL)
			{
				if ((tmp = ft_strjoin(start, tmp2)) == NULL)
					return (ft_error(0, "ERROR : strjoin0 replace_env_var", NULL, FALSE));
				if ((cmd[i] = ft_strjoin(tmp, end)) == NULL)
					return (ft_error(0, "ERROR : strjoin1 replace_env_var", NULL, FALSE));
				free(tmp2);
				free(tmp);
			}
			else
			{
				if ((cmd[i] = ft_strjoin(start, end)) == NULL)
					return (ft_error(0, "ERROR : strjoin2 replace_env_var", NULL, FALSE));
			}
			ft_strdel(&var);
			ft_strdel(&start);
			ft_strdel(&end);
		}
		else
			i++;
	}
	return (TRUE);
}
