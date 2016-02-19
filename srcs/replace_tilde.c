#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	rt1(int i, char **paths, char **env, char *env_name)
{
	char	*home;

	ft_strdel(&paths[i]);
	if ((home = get_env(env_name, env)) == NULL)
		return (TRUE);
	if ((paths[i] = ft_strdup(home)) == NULL)
		return (ft_error(0, "ERROR : DUP", paths[i], FALSE));
	free(home);
	return (2);
}

static t_bool	rt2(int i, char **paths, char **env)
{
	char	*tmp;
	char	*home;

	if ((tmp = ft_strsub(paths[i], 1, ft_strlen(paths[i]))) == NULL)
		return (ft_error(0, "ERROR : SUB", NULL, FALSE));
	ft_strdel(&paths[i]);
	if ((home = get_env("HOME", env)) == NULL)
	{
		free(tmp);
		return (TRUE);
	}
	if ((paths[i] = ft_strjoin(home, tmp)) == NULL)
		return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
	free(tmp);
	free(home);
	return (2);
}

t_bool			replace_tilde(char **paths, char **env)
{
	int		i;
	t_bool	b;

	i = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "~-"))
			b = rt1(i, paths, env, "OLDPWD");
		else if (ft_strequ(paths[i], "~+"))
			b = rt1(i, paths, env, "PWD");
		else if (paths[i][0] == '~')
			b = rt2(i, paths, env);
		if (b != 2)
			return (b);
		i++;
	}
	return (TRUE);
}
