#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		print_path(char *path, char **env, char *color)
{
	char	**home;
	size_t	i;
	t_bool	b;

	b = TRUE;
	if ((home = get_env("HOME", env)) != NULL)
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
		ft_freetstring(&home);
	}
	if (b)
		ft_putstr_color(color, path);
}

void		verif_env(char ***env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : verif_env");
#endif

	char	buff[BUFF_S];

	getcwd(buff, BUFF_S);
	if (get_env("PWD", *env) == NULL)
		set_env("PWD", env, buff);
	if (get_env("OLDPWD", *env) == NULL)
		set_env("OLDPWD", env, buff);
}

static void	init_start(char ***env, char **env2)
{
	char		**tmp;
	char		*tmp2;
	size_t		i;

	i = 0;
	tmp2 = NULL;
	while (env2 && env2[i])
		i++;
	ft_copyt2d(env, env2, i, i);
	verif_env(env);
	if ((tmp = get_env("SHLVL", *env)) != NULL)
		tmp2 = ft_itoa(ft_atoi(tmp[0]) + 1);
	else
		tmp2 = ft_strdup("1");
	if (tmp2 != NULL)
		set_env("SHLVL", env, tmp2);
	ft_strdel(&tmp2);
	ft_freetstring(&tmp);
}

static int	start(char **envarg)
{
	ft_putendl("DEBUG : START");

	char		**env;
	t_bool		b;

	env = NULL;
	init_start(&env, envarg);
	b = TRUE;
	while (b)
	{
		print_prompt(env);
		b = body(&env);
	}
	ft_freetstring(&env);

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
