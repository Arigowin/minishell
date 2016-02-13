#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		print_path(char *path, t_minishell *s, char *color)
{
	char	**home;
	size_t	i;
	t_bool	b;

	b = TRUE;
	if ((home = get_env("HOME", s)) != NULL)
	{
		i = 0;
		while (path[i] && home[0][i] && path[i] == home[0][i])
			i++;
		if (i == ft_strlen(home[0]))
		{
			ft_putstr_color(color, "~");
			ft_putstr_color(color, ft_strsub(path, i, ft_strlen(path)));
			b = FALSE;
		}
	}
	if (b)
		ft_putstr_color(color, path);
}

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
	size_t		i;

	i = 0;
	while (env[i])
		i++;
	s->nbenv = ft_copyt2d(&(s->env), env, i, i);
	verif_env(s);
}

static int	start(char **env)
{
	ft_putendl("DEBUG : START");

	t_minishell	s;
	t_bool		b;

	init_t_minishell(&s);
	init_start(&s, env);
	b = TRUE;
	while (b)
	{
		print_prompt(&s);
		b = body(&s);
	}
	ft_freet2d(&(s.env), s.nbenv);

	ft_putendl("DEBUG : END");

	return (b);
}

int			main(int ac, char **av, char **env)
{
	if (ac == 1)
		return (start(env));
	ac = 1;
	(void)av;
	return (0);
}
