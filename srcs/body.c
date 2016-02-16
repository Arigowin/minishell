#include "minishell.h"
#include "libft.h"

#include <stdio.h>
static t_bool	format_and_exec_cmd(char **t, t_minishell *s)
{
	char	*tmp;
	char	*tmp2;
	int		ret_exec;

	if ((s->paths = get_env("PATH", s)) == NULL)
		take_path_in_file(s);
	if ((tmp = search_exe(s->paths, t[0])) == NULL)
		return (ft_error(0, "command not found: ", t[0], TRUE));
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
		if ((ret_exec = execprog(tmp2, t, s->env)) == -1)
			return (ft_error(0, "exec format error: ", t[0], TRUE));
	}
	ft_strdel(&tmp2);
	return (TRUE);
}

t_bool			body(t_minishell *s)
{
	char		**t;
	t_bool		b;

	t = NULL;
	if ((readline(&t)) == FALSE)
		return (FALSE);
	if (t == NULL || t[0] == NULL)
		return (TRUE);
	if ((b = builtins(t, s)) == TRUE)
	{
		ft_freetstring(&t);
		return (TRUE);
	}
	else if (b == FALSE)
	{
		ft_freetstring(&t);
		return (FALSE);
	}
	if (format_and_exec_cmd(t, s) == TRUE)
	{
		ft_freetstring(&t);
		return (TRUE);
	}
	else
	{
		ft_freetstring(&t);
		return (FALSE);
	}
}
