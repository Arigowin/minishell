
#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define BUFF_S 1024
//#define DEBUG

typedef char	t_bool;

int			execprog(char *cmd, char **arg, char **env);
char		**get_env(char *name, char **env);
char		*format_path_exe(char *path, char *cmd);
char		*search_exe(char **paths, char *exe);
t_bool		ft_error(char *str, char *exe, t_bool ret);
void		ft_tab_to_space(char **str);
char		**readline(void);
t_bool		replace_tilde(char **paths, char **env);
int			len_to_equal(char *str);

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
