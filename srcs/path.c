#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>

void	take_path_in_file(t_minishell *s)
{
// /etc/paths
	// faire un read et tout les /n les remplacer par des : sauf le dernier
	s->paths = NULL;
}

char	*format_path_exe(char *path, char *cmd)
{

#ifdef DEBUG
	ft_putendl("DEBUG : format_path_exe");
#endif

	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || path == NULL)
		return (cmd);
	if (path[ft_strlen(path) - 1] != '/')
	{
		if ((tmp = ft_strjoin(path, "/")) == NULL)
			ft_error(0, "ERROR : join format_path_exe", path, FALSE);
	}
	if ((ret = ft_strjoin(tmp, cmd)) == NULL)
		ft_error(0, "ERROR : join2 format_path_exe", path, FALSE);
	ft_strdel(&tmp);
	return (ret);
}

char	*search_exe(char **paths, char *exe)
{

#ifdef DEBUG
	ft_putendl("DEBUG : search_exe");
#endif

	struct dirent	*dp;
	DIR				*dir;
	int				i;
	t_bool			b;

	i = 0;
	b = FALSE;
	if (exe[0] == '/' || (exe[0] == '.' && exe[1] == '/'))
		return (exe);
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
