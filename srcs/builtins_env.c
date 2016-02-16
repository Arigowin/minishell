#include "minishell.h"
#include "libft.h"

t_bool	builtins_env(char **env)
{
	print_env(env);
	return (TRUE);
}
