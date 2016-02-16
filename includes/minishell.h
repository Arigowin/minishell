#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define BUFF_S 1024
# define SEP " \t\n\0"
//#define DEBUG

# include <sys/types.h>

// fuite memoire

typedef char	t_bool;

typedef struct		s_minishell
{
	char			**env;
	size_t			nbenv;
	char			**paths;
	char			*prompt;
}					t_minishell;

typedef struct		s_lstcmd
{
	char			*data;
	struct s_lstcmd	*next;
}					t_lstcmd;

// lexer.c
char				**lexer(char *str, char *sc);

// body.c
t_bool				body(t_minishell *s);

// builtins.c
t_bool				builtins(char **t, t_minishell *s);

// builtins_cd.c
t_bool				change_directory(char **cmd, t_minishell *s);

// command_lines.c
void				ft_tab_to_space(char **str);
t_bool				readline(char ***t);
t_bool				replace_tilde(char **paths, t_minishell *s);
t_bool				replace_env_var(char **path, t_minishell *s);

// in env.c
size_t				len_to_equal(char *str);
char				**get_env(char *name, t_minishell *s);
t_bool				modif_env(char *name, t_minishell *s, char *str);
t_bool				del_env(char *name, t_minishell *s);
t_bool				add_env(char *name, t_minishell *s, char *str);
t_bool				set_env(char *name, t_minishell *s, char *str);
void				print_env(t_minishell *s);

// error.c
t_bool				ft_error(int i, char *str, char *exe, t_bool ret);

// execprog.c
int					execprog(char *cmd, char **arg, char **env);

// main.c
void				verif_env(t_minishell *s);
void				print_path(char *path, t_minishell *s, char *color);

// path.c
char				*format_path_exe(char *path, char *cmd);
char				*search_exe(char **paths, char *exe);
void				take_path_in_file(t_minishell *s);

// prompt.c
void				print_prompt(t_minishell *s);

// builtins_env.c
t_bool				builtins_env(t_minishell *s);

// free.c
void				ft_freetstring(char ***tab);


#endif

/*
** opendir
** readdir
** closedir
** - dirent
**
** malloc
** free
** exit
** - stdlib
**
** getcwd
** chdir
** fork
** close
** read
** write
** execve
** access
** - unistd
**
** stat
** lstat
** fstat
** - sys/stat
**
** open
** - fcntl
**
** wait
** waitpid
** wait3
** wait4
** - sys/wait
**
** signal
** kill
** - signal
*/
