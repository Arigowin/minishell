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

// if -/dir remplace -
int		replace_minus(char **paths, t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : replace_minus");
#endif

	char	**oldpwd;
	int		i;
	char	*tmp;
	int		nb_minus;

	i = 0;
	nb_minus = 0;
	tmp = NULL;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "-"))
		{
			ft_strdel(&paths[i]);
			if (tmp == NULL)
			{
				verif_env(s);
				oldpwd = get_env("OLDPWD", s);
				if ((paths[i] = ft_strdup(oldpwd[0])) == NULL)
					return (ft_error(0, "strdup replace_minus", paths[i], FALSE) - 1);
				tmp = paths[i];
			}
			nb_minus++;
		}
		i++;
	}
	if (tmp != NULL)
		ft_putendl(tmp);
	return (nb_minus);
}

// gerer le ./
t_bool	change_directory(char **cmd, t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : change_directory");
#endif

	int		i;
	char	buff[BUFF_S];
	char	**tmp;
	int		nb_minus;

	i = 0;
	while (cmd[i])
		i++;
	if ((nb_minus = replace_minus(cmd, s)) == -1)
		return (FALSE);
	if ((i - (nb_minus == 0 ? 0 : nb_minus)) > 2)
		return (ft_error(1, "too many arguments", NULL, TRUE));
	if (cmd[1] == NULL)
	{
		if ((tmp = get_env("HOME", s)) == NULL)
		{
			ft_putendl("cd: No home directory.");
			return (TRUE);
		}
		if (chdir(tmp[0]) == -1)
			return (FALSE);
	}
	i = 1;
	while (cmd[i])
	{
		if (chdir(cmd[i]) == -1)
			return (ft_error(1, "no such file or directory: ", cmd[i], TRUE));
		i++;
	}
	verif_env(s);
	getcwd(buff, BUFF_S);
	tmp = get_env("PWD", s);
	modif_env("OLDPWD", s, tmp[0]);
	modif_env("PWD", s, buff);
	return (TRUE);
}

// executer /bin/ls
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
