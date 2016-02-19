#include "minishell.h"
#include "libft.h"

static void		initptfunc(t_bool (*tab[5])(char **, char ***))
{
	tab[0] = &builtins_exit;
	tab[1] = &builtins_setenv;
	tab[2] = &builtins_unsetenv;
	tab[3] = &builtins_env;
	tab[4] = &change_directory;
}

t_bool			builtins(char **t, char ***env)
{
	t_ptfu	tab[5];
	char	*name[5] = {"exit", "setenv", "unsetenv", "env", "cd"};
	int		i;

	if (replace_tilde(t, *env) == FALSE)
		return (FALSE);
	if (replace_env_var(t, *env) == FALSE)
		return (FALSE);
	initptfunc(tab);
	i = 0;
	while (i < 5)
	{
		if (ft_strequ(name[i], t[0]))
			break ;
		i++;
	}
	if (i < 5)
		return (tab[i](t, env));
	return (2);
}
