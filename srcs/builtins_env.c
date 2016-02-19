#include "minishell.h"

t_bool	builtins_env(char **t, char ***env)
{
	if (t[1] && t[1][0] == '-' && t[1][1] == 'u')
		return (builtins_unsetenv(t, env));
	else if (t[1] && t[1][0] == '-' && t[1][1] == 'i')
		return (2);
	print_env(*env);
	return (TRUE);
}
