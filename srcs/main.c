#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int		execprog(char *cmd, char **arg, char **env)
{
	pid_t	father;
	int		ret;

	ret = 0;
	father = fork();
	if (father == 0)
	{
		ret = execve(cmd, arg, env);
	}
	else
	{
		waitpid(father, NULL, 0);
	}
	return (ret);
}

char	**readline()
{
	char	*line;

	get_next_line(0, &line);
	return (ft_strsplit(line, ' '));
}

char	**get_path(char **env)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		tmp = ft_strsub(env[i], 0, 4);
		if (ft_strcmp(tmp, "PATH") == 0)
		{
			ft_strdel(&tmp);
			tmp = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
			ret = ft_strsplit(tmp, ':');
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
		tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, cmd);
	ft_strdel(&tmp);
	return (ret);
}

char	*search_exe(char **paths, char *exe)
{
// chercher la commande dans chaque path et renvoyer celle ou la commande a ete trouver
	(void)exe;
	return (paths[4]);
}

int		body(char **env)
{
	char	**t;
	char	**paths;
	char	*tmp;
	int		ret_exec;

	ft_putstr("$> ");
	t = readline();
	if (strcmp(t[0], "exit") == 0)
	{
		printf("%s\n", t[0]);
		return (0);
	}
	paths = get_path(env);
	tmp = search_exe(paths, t[0]);
	tmp = format_path_exe(tmp, t[0]);
	ret_exec = execprog(tmp, t, NULL);
	if (ret_exec == -1)
		printf("ERROR\n");
	return (1);
}

int main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		while (body(env))
			;
	}
	ac = 1;
	(void)av;
	return (0);
}
