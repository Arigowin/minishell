#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int		execprog(char *cmd, char **arg, char **env)
{
	pid_t	father;

	printf("OK\n");
	father = fork();
	if (father == 0)
	{
		if (execve(cmd, arg, env) == -1)
			printf("ERROR\n");
	}
	else
	{
		waitpid(father, NULL, 0);
	}
	return (0);
}

char	**readline()
{
	char	*line;

	get_next_line(0, &line);
	return (ft_strsplit(line, ' '));
}

void	test(char **env)
{
	char	**t;

	t = readline();
	execprog(t[0], t, env);
	env[0][0] = 0;
}

int main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		test(env);
	}
	ac = 1;
	(void)av;
	return (0);
}
