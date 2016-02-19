#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	format_and_exec_cmd(char **t, char **env)
{
	char	*tmp;
	char	*tmp2;
	char	**paths;
	int		ret_exec;

	if ((paths = take_path(env)) == NULL)
		return (ft_error(0, "not PATH found", t[0], TRUE));
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error(0, "command not found: ", t[0], TRUE));
	ft_freetstring(&paths);
	if ((tmp2 = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	ft_strdel(&tmp);
	if ((ft_strequ(t[0], "env") && ft_strequ(t[1], "-i")))
	{
		if ((ret_exec = execprog(tmp2, t, NULL)) == -1)
			return (ft_error(0, "exec format error: ", t[0], TRUE));
	}
	else
	{
		if ((ret_exec = execprog(tmp2, t, env)) == -1)
			return (ft_error(0, "exec format error: ", t[0], TRUE));
	}
	free(tmp2);
	return (TRUE);
}

t_bool			body(char ***env)
{
	char		**t;
	t_bool		b;

	t = NULL;
	if ((readline(&t)) == FALSE)
		return (FALSE);
	if (t == NULL || t[0] == NULL)
		return (TRUE);
	if ((b = builtins(t, env)) == TRUE)
	{
		ft_freetstring(&t);
		return (TRUE);
	}
	else if (b == FALSE)
	{
		ft_freetstring(&t);
		return (FALSE);
	}
	if (format_and_exec_cmd(t, *env) == TRUE)
	{
		ft_freetstring(&t);
		return (TRUE);
	}
	ft_freetstring(&t);
	return (FALSE);
}
