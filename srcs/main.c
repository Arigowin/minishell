#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// cd
// cd -		=> OLDPWD
// cd		=> PWD
// cd libft includes => cd libft ; cd includes
t_bool	change_directory(char **cmd)
{
	char	*t[2] = {".", NULL};
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 3)
		return (ft_error("too many arguments", NULL, TRUE));
	i = 1;
	while (cmd[i])
	{
		// a ramplacer par une autre fonction qui accepte les ../..
		if (search_exe(t, cmd[i]) == NULL)
			return (ft_error("no such file or directory: ", cmd[i], TRUE));
		if (chdir(cmd[i]) == -1)
			return (FALSE);
		i++;
	}
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
		return (change_directory(t));
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
