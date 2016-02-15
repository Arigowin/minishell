#include "minishell.h"
#include "libft.h"

#include <stdio.h>
static t_bool	format_and_exec_cmd(char **t, t_minishell *s)
{
	char	*tmp;
	int		ret_exec;

	if ((s->paths = get_env("PATH", s)) == NULL)
		take_path_in_file(s);
	if ((tmp = search_exe(s->paths, t[0])) == NULL)
		return (ft_error(0, "command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if ((ft_strequ(t[0], "env") && ft_strequ(t[1], "-i")))
	{
		if ((ret_exec = execprog(tmp, t, NULL)) == -1)
			return (ft_error(0, "exec format error: ", t[0], TRUE));
	}
	else
	{
		if ((ret_exec = execprog(tmp, t, s->env)) == -1)
			return (ft_error(0, "exec format error: ", t[0], TRUE));
	}
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
		return (TRUE);
	else if (b == FALSE)
		return (FALSE);
	return (format_and_exec_cmd(t, s));
}
