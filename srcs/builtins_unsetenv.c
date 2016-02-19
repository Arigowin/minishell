#include "minishell.h"

t_bool			builtins_unsetenv(char **t, char ***env)
{
	int		i;

	i = 0;
	while (t[i])
	{
		if (env_exist(t[i], *env))
			del_env(t[i], env);
		i++;
	}
	return (TRUE);
}
