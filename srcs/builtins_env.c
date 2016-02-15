#include "minishell.h"
#include "libft.h"

t_bool	builtins_env(t_minishell *s)
{
	print_env(s);
	return (TRUE);
}
