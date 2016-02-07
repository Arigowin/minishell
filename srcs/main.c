#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_bool	replace_minus(char **paths, char **env)
{
	char	**oldpwd;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "-"))
		{
			ft_strdel(&paths[i]);
			oldpwd = get_env("OLDPWD", env);
			if ((paths[i] = ft_strdup(oldpwd[0])) == NULL)
				return (ft_error("strdup replace_minus", paths[i], FALSE));
		}
		i++;
	}
	return (TRUE);
}

t_bool	set_env(char *name, char **env, char *str)
{
	char	*tmp;
	int		i;
	int		len;
	t_bool	b;

	i = 0;
	b = FALSE;
	while (env[i] && !b)
	{
		len = len_to_equal(env[i]);
		tmp = ft_strsub(env[i], 0, len);
		if (ft_strcmp(tmp, name) == '=')
		{
			b = TRUE;
			env[i] = ft_strjoin(tmp, str);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	return (b);
}

// cd
// cd libft includes => cd libft ; cd includes
// cd libft a => cd: string not in pwd: libft
t_bool	change_directory(char **cmd, char **env)
{
	int		i;
	char	buff[BUFF_S];
	char	**tmp;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 3)
		return (ft_error("too many arguments", NULL, TRUE));
	i = 1;
	if (replace_minus(cmd, env) == FALSE)
		return (FALSE);
	if (cmd[1] == NULL)
	{
		tmp = get_env("HOME", env);
		if (chdir(tmp[0]) == -1)
			return (FALSE);
	}
	while (cmd[i])
	{
		// a ramplacer par une autre fonction qui accepte les ../..
		//		if (search_exe(t, cmd[i]) == NULL)
		//			return (ft_error("no such file or directory: ", cmd[i], TRUE));
		if (chdir(cmd[i]) == -1)
			return (FALSE);
		i++;
	}
	getcwd(buff, BUFF_S);
	ft_putendl(buff);
	tmp = get_env("PWD", env);
	set_env("OLDPWD", env, tmp[0]);
	set_env("PWD", env, buff);
	return (TRUE);
}

// env
void	print_env(char **env)
{
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

int		body(char **env)
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
	if (replace_tilde(t, env) == FALSE)
		return (FALSE);
	else if (ft_strequ(t[0], "cd"))
		return (change_directory(t, env));
	else if (ft_strequ(t[0], "env"))
	{
		print_env(env);
		return (TRUE);
	}
	if ((paths = get_env("PATH", env)) == NULL)
		return (ft_error("PATH not found ", t[0], TRUE));
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error("command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if ((ret_exec = execprog(tmp, t, NULL)) == -1)
		return (ft_error("exec format error: ", t[0], TRUE));
	return (TRUE);
}

int		main(int ac, char **av, char **env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : START");
#endif

	t_bool	b;

	if (ac == 1)
	{
		b = TRUE;
		while (b)
		{
			ft_putstr("$> ");
			b = body(env);
		}
	}
	ac = 1;
	(void)av;

#ifdef DEBUG
	ft_putendl("DEBUG : END");
#endif

	return (0);
}
