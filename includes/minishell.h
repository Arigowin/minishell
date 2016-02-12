
#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define BUFF_S 1024
//#define DEBUG

# include <sys/types.h>

typedef char	t_bool;

typedef struct	s_minishell
{
	char		**env;
	size_t		nbenv;
	char		**paths;
}				t_minishell;

int				execprog(char *cmd, char **arg, char **env);
char			*format_path_exe(char *path, char *cmd);
char			*search_exe(char **paths, char *exe);
t_bool			ft_error(int i, char *str, char *exe, t_bool ret);
void			ft_tab_to_space(char **str);
char			**readline(void);
t_bool			replace_tilde(char **paths, t_minishell *s);
void			verif_env(t_minishell *s);
void			take_path_in_file(t_minishell *s);

// env
size_t			len_to_equal(char *str);
char			**get_env(char *name, t_minishell *s);

// in env.c
t_bool			modif_env(char *name, t_minishell *s, char *str);
t_bool			del_env(char *name, t_minishell *s);
t_bool			add_env(char *name, t_minishell *s, char *str);
t_bool			set_env(char *name, t_minishell *s, char *str);
void			print_env(t_minishell *s);

// cd
int				replace_minus(char **paths, t_minishell *s);
t_bool			change_directory(char **cmd, t_minishell *s);

#endif

/*
* opendir
* readdir
* closedir
* - dirent
*
* malloc
* free
* exit
* - stdlib
*
* getcwd
* chdir
* fork
* close
* read
* write
* execve
* access
* - unistd
*
* stat
* lstat
* fstat
* - sys/stat
*
* open
* - fcntl
*
* wait
* waitpid
* wait3
* wait4
* - sys/wait
*
* signal
* kill
* - signal
*/
