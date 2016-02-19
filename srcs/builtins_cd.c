#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int		replace_minus_bis(char ***env, char *oldpwd, int i, char **p)
{
	verif_env(env);
	oldpwd = get_env("OLDPWD", *env);
	if ((p[i] = ft_strdup(oldpwd)) == NULL)
		return (ft_error(0, "ERROR : DUP", p[i], FALSE) - 1);
	free(oldpwd);
	return (i);
}

static int		replace_minus(char **paths, char ***env)
{
	char	*oldpwd;
	int		i;
	int		pos;
	int		nb_minus;

	i = -1;
	nb_minus = 0;
	pos = 0;
	oldpwd = NULL;
	while (paths[++i])
	{
		if (ft_strequ(paths[i], "-"))
		{
			ft_strdel(&paths[i]);
			if (pos == 0)
				pos = replace_minus_bis(env, oldpwd, i, paths);
			nb_minus++;
		}
	}
	if (pos != 0)
	{
		print_path(paths[pos], *env, "");
		ft_putendl("");
	}
	return (nb_minus);
}

static t_bool	cd_home(char ***env)
{
	char	*tmp;

	if ((tmp = get_env("HOME", *env)) == NULL)
	{
		ft_putendl("cd: No home directory.");
		return (TRUE);
	}
	if (chdir(tmp) == -1)
		return (FALSE);
	free(tmp);
	return (TRUE);
}

static t_bool	cd_to(char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (access(cmd[i], F_OK))
			return (ft_error(1, "no such file or directory: ", cmd[i], TRUE));
		if (chdir(cmd[i]) == -1)
			return (ft_error(1, "permission denied: ", cmd[i], TRUE));
		i++;
	}
	return (TRUE);
}

t_bool			change_directory(char **cmd, char ***env)
{
	int		i;
	int		nb_minus;
	char	buff[BUFF_S];
	char	*tmp;

	i = 0;
	while (cmd[i])
		i++;
	if ((nb_minus = replace_minus(cmd, env)) == -1)
		return (FALSE);
	if ((i - (nb_minus == 0 ? 0 : nb_minus)) > 2)
		return (ft_error(1, "too many arguments", NULL, TRUE));
	if (cmd[1] == NULL)
		cd_home(env);
	cd_to(cmd);
	verif_env(env);
	if (getcwd(buff, BUFF_S) == NULL)
		return (FALSE);
	tmp = get_env("PWD", *env);
	modif_env("OLDPWD", env, tmp);
	free(tmp);
	modif_env("PWD", env, buff);
	return (TRUE);
}
