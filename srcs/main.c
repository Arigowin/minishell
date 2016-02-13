#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		verif_env(t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : verif_env");
#endif

	char	buff[BUFF_S];

	getcwd(buff, BUFF_S);
	if (get_env("PWD", s) == NULL)
		set_env("PWD", s, buff);
	if (get_env("OLDPWD", s) == NULL)
		set_env("OLDPWD", s, buff);
}

static void	init_t_minishell(t_minishell *s)
{
	s->env = NULL;
	s->nbenv = 0;
	s->paths = NULL;
	s->prompt = "$> ";
}

static void	init_start(t_minishell *s, char **env)
{
	s->nbenv = ft_copyt2d(&(s->env), env);
	verif_env(s);
}

static int	start(char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : body");
#endif

	t_minishell	s;
	t_bool		b;

	init_t_minishell(&s);
	init_start(&s, env);
	b = TRUE;
	while (b)
	{
		ft_putstr(s.prompt);
		b = body(&s);
	}
	ft_freet2d(&(s.env), s.nbenv);
	return (b);
}

int			main(int ac, char **av, char **env)
{

	ft_putendl("DEBUG : START");

	if (ac == 1)
		return (start(env));
	ac = 1;
	(void)av;

	ft_putendl("DEBUG : END");

	return (0);
}
