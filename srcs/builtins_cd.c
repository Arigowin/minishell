#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static int		replace_minus(char **paths, char ***env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : replace_minus");
#endif

	char	**oldpwd;
	int		i;
	int		pos;
	int		nb_minus;

	i = 0;
	nb_minus = 0;
	pos = 0;
	while (paths[i])
	{
		if (ft_strequ(paths[i], "-"))
		{
			ft_strdel(&paths[i]);
			if (pos == 0)
			{
				verif_env(env);
				oldpwd = get_env("OLDPWD", *env);
				if ((paths[i] = ft_strdup(oldpwd[0])) == NULL)
					return (ft_error(0, "strdup replace_minus", paths[i], FALSE) - 1);
				pos = i;
				ft_freetstring(&oldpwd);
			}
			nb_minus++;
		}
		i++;
	}
	if (pos != 0)
	{
		print_path(paths[pos], *env, "");
		ft_putendl("");
	}
	return (nb_minus);
}

t_bool			change_directory(char **cmd, char ***env)
{

#ifdef DEBUG
	ft_putendl("DEBUG : change_directory");
#endif

	int		i;
	int		nb_minus;
	char	buff[BUFF_S];
	char	**tmp;

	i = 0;
	while (cmd[i])
		i++;
	if ((nb_minus = replace_minus(cmd, env)) == -1)
		return (FALSE);
	if ((i - (nb_minus == 0 ? 0 : nb_minus)) > 2)
		return (ft_error(1, "too many arguments", NULL, TRUE));
	if (cmd[1] == NULL)
	{
		if ((tmp = get_env("HOME", *env)) == NULL)
		{
			ft_putendl("cd: No home directory.");
			return (TRUE);
		}
		if (chdir(tmp[0]) == -1)
			return (FALSE);
		ft_freetstring(&tmp);
	}
	i = 1;
	while (cmd[i])
	{
		if (access(cmd[i], F_OK))
			return (ft_error(1, "no such file or directory: ", cmd[i], TRUE));
		if (chdir(cmd[i]) == -1)
			return (ft_error(1, "permission denied: ", cmd[i], TRUE));
		i++;
	}
	verif_env(env);
	getcwd(buff, BUFF_S);
	tmp = get_env("PWD", *env);
	modif_env("OLDPWD", env, tmp[0]);
	ft_freetstring(&tmp);
	modif_env("PWD", env, buff);
	return (TRUE);
}
