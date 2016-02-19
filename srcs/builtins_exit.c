#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_bool			builtins_exit(char **t, char ***env)
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
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(t[1]));
	}
	else
		exit(0);
	return (FALSE);
}
