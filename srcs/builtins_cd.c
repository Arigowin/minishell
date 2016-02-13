#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static int		replace_minus(char **paths, t_minishell *s)
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

t_bool			change_directory(char **cmd, t_minishell *s)
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
		if (access(cmd[i], F_OK))
			return (ft_error(1, "no such file or directory: ", cmd[i], TRUE));
		if (chdir(cmd[i]) == -1)
			return (ft_error(1, "permission denied: ", cmd[i], TRUE));
		i++;
	}
	verif_env(s);
	getcwd(buff, BUFF_S);
	tmp = get_env("PWD", s);
	modif_env("OLDPWD", s, tmp[0]);
	modif_env("PWD", s, buff);
	return (TRUE);
}
