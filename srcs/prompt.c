#include "minishell.h"
#include "libft.h"

void		print_prompt(t_minishell *s)
{
	char	**tmp;

	if ((tmp = get_env("PWD", s)) != NULL)
	{
		print_path(tmp[0], s, BLUE);
		ft_putstr_color(GREEN, "\n$> ");
	}
	else
		ft_putstr(s->prompt);
}

