#include "minishell.h"
#include "libft.h"

#include <stdio.h>
void		print_prompt(char **env)
{
	char	**tmp;

	if ((tmp = get_env("PWD", env)) != NULL)
	{
		print_path(tmp[0], env, BLUE);
		ft_putstr_color(GREEN, "\n$> ");
	}
	else
		ft_putstr("$> ");
	ft_freetstring(&tmp);
}

