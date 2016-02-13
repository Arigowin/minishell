#include "minishell.h"
#include "libft.h"

static t_bool	builtins_exit()
{
	ft_putendl("exit");
	return (FALSE);
}

static t_bool	builtins_env(t_minishell *s)
{
	print_env(s);
	return (TRUE);
}

static t_bool	builtins_setenv(char **t, t_minishell *s)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	if (i > 3)
		return (ft_error(2, "Too many arguments.", NULL, TRUE));
	if (t[1] != NULL)
		return (set_env(t[1], s, t[2]));
	else
		print_env(s);
	return (TRUE);
}

static t_bool	builtins_unsetenv(char **t, t_minishell *s)
{
	int		i;

	i = 1;
	while (t[i])
	{
		del_env(t[i], s);
		i++;
	}
	return (TRUE);
}

t_bool			builtins(char **t, t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : builtins");
#endif

	if (ft_strequ(t[0], "exit"))
		return (builtins_exit());
	if (replace_tilde(t, s) == FALSE)
		return (FALSE);
	else if (ft_strequ(t[0], "cd"))
		return (change_directory(t, s));
	else if (ft_strequ(t[0], "env"))
		return (builtins_env(s));
	else if (ft_strequ(t[0], "setenv"))
		return (builtins_setenv(t, s));
	else if (ft_strequ(t[0], "unsetenv"))
		return (builtins_unsetenv(t, s));
	return (2);
}
