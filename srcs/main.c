#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		replace_minus(char **paths, char **env)
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
				oldpwd = get_env("OLDPWD", env);
				if ((paths[i] = ft_strdup(oldpwd[0])) == NULL)
					return (ft_error("strdup replace_minus", paths[i], FALSE) - 1);
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

t_bool	modif_env(char *name, char **env, char *str)
{

#ifdef DEBUG
	ft_putendl("DEBUG : modif_env");
#endif

	char	*tmp;
	int		i;
	int		len;
	t_bool	b;

	i = 0;
	b = FALSE;
	while (env[i] && env[i][0] && !b)
	{
		len = len_to_equal(env[i]);
		tmp = ft_strsub(env[i], 0, len);
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			if (str != NULL)
				env[i] = ft_strjoin(tmp, str);
			else
				env[i] = ft_strdup(tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
	{
		tmp = ft_strjoin(name, "=");
		env[i] = ft_strjoin(tmp, str);
		b = TRUE;
	}
	i = 0;
	return (b);
}

t_bool	del_env(char *name, t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : del_env");
#endif

	char	*tmp;
	char	**tmpenv;
	int		i;
	int		j;
	int		len;
	t_bool	b;

	i = 0;
	j = 0;
	b = FALSE;
	tmpenv = (char **)malloc(sizeof(char *) * s->nbenv);
	while ((s->env)[i] && (s->env)[i][0])
	{
		tmpenv[j] = NULL;
		len = len_to_equal((s->env)[i]);
		tmp = ft_strsub((s->env)[i], 0, len);
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			s->nbenv--;
		}
		else
		{
			tmpenv[j] = ft_strdup((s->env)[i]);
			j++;
		}
		i++;
	}
	tmpenv[j] = NULL;
	ft_freet2d(&(s->env));
	ft_copyt2d(&(s->env), tmpenv);
	ft_freet2d(&tmpenv);
	return (b);
}

t_bool	add_env(char *name, t_minishell *s, char *str)
{

#ifdef DEBUG
	ft_putendl("DEBUG : add_env");
#endif
	char	**tmpenv;
	char	*tmp;

	tmpenv = (char **)malloc(sizeof(char *) * (s->nbenv + 1));
	ft_copyt2d(&tmpenv, s->env);
	ft_freet2d(&(s->env));
	tmp = ft_strjoin(name, "=");
	tmpenv[s->nbenv] = ft_strjoin(tmp, str);
	ft_strdel(&tmp);
	s->nbenv++;
	tmpenv[s->nbenv] = NULL;
	ft_copyt2d(&(s->env), tmpenv);
	ft_freet2d(&tmpenv);
	return (TRUE);
}

// cd
t_bool	change_directory(char **cmd, char **env)
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
	if ((nb_minus = replace_minus(cmd, env)) == -1)
		return (FALSE);
	if ((i - (nb_minus == 0 ? 0 : nb_minus)) > 2)
		return (ft_error("too many arguments", NULL, TRUE));
	if (cmd[1] == NULL)
	{
		if ((tmp = get_env("HOME", env)) == NULL)
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
			return (ft_error("no such file or directory: ", cmd[i], TRUE));
		i++;
	}
	getcwd(buff, BUFF_S);
	tmp = get_env("PWD", env);
	modif_env("OLDPWD", env, tmp[0]);
	modif_env("PWD", env, buff);
	return (TRUE);
}

// env
void	print_env(char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : print_env");
#endif

	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}
// setenv
// unsetenv

int		body(t_minishell *s)
{

#ifdef DEBUG
	ft_putendl("DEBUG : body");
#endif

	char	**t;
	char	**paths;
	char	*tmp;
	int		ret_exec;

	if ((t = readline()) == NULL)
		return (TRUE);
	if (ft_strequ(t[0], "exit"))
	{
		ft_putendl("exit");
		return (FALSE);
	}
	if (replace_tilde(t, s->env) == FALSE)
		return (FALSE);
	else if (ft_strequ(t[0], "cd"))
		return (change_directory(t, s->env));
	else if (ft_strequ(t[0], "env"))
	{
		print_env(s->env);
		return (TRUE);
	}
	else if (ft_strequ(t[0], "setenv"))
		return (add_env(t[1], s, t[2]));
	else if (ft_strequ(t[0], "unsetenv"))
		return (del_env(t[1], s));
	if ((paths = get_env("PATH", s->env)) == NULL)
		return (ft_error("PATH not found ", t[0], TRUE));
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error("command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if ((ret_exec = execprog(tmp, t, NULL)) == -1)
		return (ft_error("exec format error: ", t[0], TRUE));
	return (TRUE);
}

void	verif_env(t_minishell *s)
{
	char	buff[BUFF_S];

	getcwd(buff, BUFF_S);
	if (get_env("PWD", s->env) == NULL)
		add_env("PWD", s, buff);
	if (get_env("OLDPWD", s->env) == NULL)
		add_env("OLDPWD", s, buff);
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
		printf("%zu\n", s.nbenv);
		verif_env(&s);
		b = TRUE;
		while (b)
		{
			ft_putstr("$> ");
			b = body(&s);
		}
		ft_freet2d(&(s.env));
	}
	ac = 1;
	(void)av;

#ifdef DEBUG
	ft_putendl("DEBUG : END");
#endif

	return (0);
}
