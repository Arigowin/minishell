#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_bool	builtins_exit(char **t, char ***env)
{
	size_t	i;

	ft_putendl("exit");
	ft_freetstring(env);
	i = 0;
	if (t[1] != NULL)
	{
		while (t[1][i])
		{
			if (!ft_isdigit(t[1][i]))
			{
				ft_putstr("exit: ");
				ft_putstr(t[1]);
				ft_putendl(": numeric argument required");
				exit (255);
			}
			i++;
		}
		exit (ft_atoi(t[1]));
	}
	else
		exit (0);
	return (FALSE);
}

static t_bool	builtins_setenv(char **t, char ***env)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	if (i > 3)
		return (ft_error(2, "Too many arguments.", NULL, TRUE));
	if (t[1] != NULL)
		return (set_env(t[1], env, t[2]));
	else
		print_env(*env);
	return (TRUE);
}

static t_bool	builtins_unsetenv(char **t, char ***env, int i)
{
	while (t[i])
	{
		if (env_exist(t[i], *env))
			del_env(t[i], env);
		i++;
	}
	return (TRUE);
}

t_bool			builtins(char **t, char ***env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : builtins");
#endif

	if (ft_strequ(t[0], "exit"))
		return (builtins_exit(t, env));
	if (replace_tilde(t, *env) == FALSE)
		return (FALSE);
	if (replace_env_var(t, *env) == FALSE)
		return (FALSE);
	else if (ft_strequ(t[0], "cd"))
		return (change_directory(t, env));
	else if (ft_strequ(t[0], "setenv"))
		return (builtins_setenv(t, env));
	else if (ft_strequ(t[0], "unsetenv"))
		return (builtins_unsetenv(t, env, 1));
	else if ((ft_strequ(t[0], "env") && ft_strequ(t[1], "-u")))
		return (builtins_unsetenv(t, env, 2));
	else if (ft_strequ(t[0], "env") && ft_strchr(t[1], '-') == NULL)
		return (builtins_env(*env));
	return (2);
}
