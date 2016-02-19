#include "minishell.h"

t_bool	builtins_env(char **t, char ***env)
{
	if (t[1] && t[1][0] == '-')
	{
		return (builtins_unsetenv(t, env));
	}
	print_env(*env);
	return (TRUE);
}
