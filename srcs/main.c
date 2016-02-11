#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	verif_env(t_minishell *s)
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

// executer /bin/ls
// gerer le ./
int		body(t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : body");
#endif

	char	**t;
	char	**paths;
	char	*tmp;
	int		ret_exec;
	int		i;
	t_bool	b;

	if ((t = readline()) == NULL)
		return (TRUE);
	if (ft_strequ(t[0], "exit"))
	{
		ft_putendl("exit");
		return (FALSE);
	}
	if (replace_tilde(t, s) == FALSE)
		return (FALSE);
	else if (ft_strequ(t[0], "cd"))
		return (change_directory(t, s));
	else if (ft_strequ(t[0], "env"))
	{
		print_env(s);
		return (TRUE);
	}
	else if (ft_strequ(t[0], "setenv"))
	{
		i = 0;
		while (t[i])
			i++;
		if (i > 3)
			return (ft_error(2, "Too many arguments.", NULL, TRUE));
		if (t[1] != NULL)
			return (set_env(t[1], s, t[2]));
		else
			print_env(s);
		return (TRUE);
	}
	else if (ft_strequ(t[0], "unsetenv"))
	{
		i = 1;
		while (t[i])
		{
			b = del_env(t[i], s);
			i++;
		}
		return (TRUE);
	}
	if ((paths = get_env("PATH", s)) == NULL)
		return (ft_error(0, "PATH not found ", t[0], TRUE));
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error(0, "command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if ((ret_exec = execprog(tmp, t, NULL)) == -1)
		return (ft_error(0, "exec format error: ", t[0], TRUE));
	return (TRUE);
}

int		main(int ac, char **av, char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : START");
#endif

	t_minishell	s;
	t_bool	b;

	if (ac == 1)
	{
		s.nbenv = ft_copyt2d(&(s.env), env);
		verif_env(&s);
		b = TRUE;
		while (b)
		{
			ft_putstr("$> ");
			b = body(&s);
		}
		ft_freet2d(&(s.env), s.nbenv);
	}
	ac = 1;
	(void)av;

#ifdef DEBUG
	ft_putendl("DEBUG : END");
#endif

	return (0);
}
