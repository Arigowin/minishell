
#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

typedef char bool;

int			execprog(char *cmd, char **arg, char **env);
char		**get_env(char *name, char **env);
char		*format_path_exe(char *path, char *cmd);
char		*search_exe(char **paths, char *exe);
bool		ft_error(char *str, char *exe, bool ret);

#endif

/*
 * opendir
 * readdir
 * closedir
 * - dirent

 * malloc
 * free
 * exit
 * - stdlib

 * getcwd
 * chdir
 * fork
 * close
 * read
 * write
 * execve
 * access
 * - unistd

 * stat
 * lstat
 * fstat
 * - sys/stat

 * open
 * - fcntl

 * wait
 * waitpid
 * wait3
 * wait4
 * - sys/wait

 * signal
 * kill
 * - signal

 */
