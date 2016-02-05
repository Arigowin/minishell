#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>

char	**get_env(char *name, char **env)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		tmp = ft_strsub(env[i], 0, 4);
		if (ft_strcmp(tmp, name) == 0)
		{
			ft_strdel(&tmp);
			if ((tmp = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5)) ==NULL)
				ft_putendl_fd("ERROR : sub get_env", 2);
			if ((ret = ft_strsplit(tmp, ':')) == NULL)
				ft_putendl_fd("ERROR : split get_env", 2);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	ft_strdel(&tmp);
	return (ret);
}

char	*format_path_exe(char *path, char *cmd)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (path[ft_strlen(path) - 1] != '/')
	{
		if ((tmp = ft_strjoin(path, "/")) == NULL)
			ft_putendl_fd("ERROR : join format_path_exe", 2);
	}
	if ((ret = ft_strjoin(tmp, cmd)) == NULL)
		ft_putendl_fd("ERROR : join2 format_path_exe", 2);
	ft_strdel(&tmp);
	return (ret);
}

char	*search_exe(char **paths, char *exe)
{
	struct dirent	*dp;
	DIR				*dir;
	int				i;
	bool			b;

	i = 0;
	b = FALSE;
	while (paths[i] != NULL && !b)
	{
		if ((dir = opendir(paths[i])) != NULL)
		{
			while ((dp = readdir(dir)) != NULL && !b)
			{
				if (ft_strequ(dp->d_name, exe))
					b = TRUE;
			}
			closedir(dir);
		}
		i++;
	}
	if (b)
		return (paths[i - 1]);
	return (NULL);
}
