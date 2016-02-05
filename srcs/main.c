#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

char	**readline()
{
	char	*line;

	get_next_line(0, &line);
	return (ft_strsplit(line, ' '));
}

int		body(char **env)
{
	char	**t;
	char	**paths;
	char	*tmp;
	int		ret_exec;

	t = readline();
	if (strcmp(t[0], "exit") == 0)
	{
		printf("%s\n", t[0]);
		exit (0);
	}
	paths = get_env("PATH", env);
	if ((tmp = search_exe(paths, t[0])) == NULL)
		return (ft_error("command not found: ", t[0], TRUE));
	if ((tmp = format_path_exe(tmp, t[0])) == NULL)
		return (TRUE);
	if ((ret_exec = execprog(tmp, t, NULL)) == -1)
		return (ft_error("exec format error: ", t[0], TRUE));
	return (TRUE);
}

int main(int ac, char **av, char **env)
{
	bool	b;

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
	return (0);
}
