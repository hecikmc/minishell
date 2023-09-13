/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:24:20 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/13 20:23:56 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HEADER ("\n\033[32;1m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\n\
                A simple shell implemented in C                    \n\
                             By                                    \n\
                --- lumorale && jmerchan ---                       \n\
\n\033[0m")

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libgen.h>
# include <signal.h>
# include <fcntl.h>

# define CMD_ERROR "Command not found\n"
# define PIPE_ERROR "Pipe error\n"
# define HEREDOC_FILE "/tmp/__spedismaracatermicers__"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*infile;
	int		infile_redirect;
	char	*outfile;
	int		outfile_redirect;
}	t_cmd;

typedef struct s_pipe
{
	char	**envp;
	char	**path;
	int		tube[2];
	int		fd_in;
	int		tmp_in;
	int		fd_out;
	int		tmp_out;
	int		n_cmd;
	int		shell_exit;
}	t_pipe;

typedef enum s_typetoken
{
	WORD,
	RED_OUT,
	RED_IN,
	RED_APPEND,
	RED_HERE,
}	t_typetoken;

/*Functions for minishell.c*/
void	ft_getline(t_pipe *pipex);

/*Functions for pipe.c*/
void	child_generator(t_pipe *pipex, t_cmd *cmd);

/*Functions for pipe_utils.c*/
//void	sub_dup2(int zero, int one);
int		redir_check(t_pipe *pipex, t_cmd *cmd, int i);

/*Functions for error.c*/
void	argc_error(void);
void	err_msg(char *str);
void	err_msg_exit(char *str);
void	err_msg_sintax(char *str);

/*Functions for free.c*/
void	free_matrix(char **str);
//void	close_pipes(int *tube);
void	free_cmd_structure(t_cmd *cmd);
void	free_pipe_structure(t_pipe *pipex);
void	ft_free_cmds(t_cmd *cmd, t_pipe *pipex);

/*Functions for checker.c*/
char	*ft_checkpipe(char *input, t_pipe *pipex);
int		ft_checksintaxpipex(char *input);

/*Functions for split_pipex.c*/
char	**ft_split_shell(char *str, char c);
int		ft_foundquotes(char *str, int *i);

/*Functions for signals.c*/
void	sigint_handler(int sig);

/*Functions for *.c from builtins*/
int		builting(t_cmd *cmd, t_pipe *pipex);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd, t_pipe *pipex);
void	ft_export(t_cmd *cmd, t_pipe *pipex, int i);
void	ft_unset(t_cmd *cmd, t_pipe *pipex);
void	ft_env(t_pipe *pipex);
void	ft_exit(t_cmd *cmd, t_pipe *pipex);

/*Functions for utils_checker.c*/
int		ft_checkquotes(char *input);
char	**ft_cleanspaces(char **split);
void	ft_getpath(t_pipe *pipex);
char	*ft_getcmd(t_pipe pipex, char *cmd);

/* Functions for general_utils.c*/
char	**ft_addarray(char *str, char **array);
char	**ft_deleteitem(int pos, char **array);
char	**ft_arraydup(char **array);
int		ft_sizearray(char **array);
int		ft_foundenv(char *var, char **envp);

/* Functions for sintax_pipe.c*/
int		ft_checksintaxpipex(char *input);
int		ft_countpipe(char *input);

/*Functions for sintax_redirect.c*/
int		ft_checkredirect(char *input);
int		ft_existred(char *input);

/*Functions for get_input.c*/
t_cmd	*ft_getinput(char *input, t_pipe *pipex);

/*Functions for utils_getinput.c*/
void	ft_heredoc(t_cmd *cmd);
char	*ft_getname(char *cmd, int *j);

/*Functions for expand.c*/
char	*ft_expandit(char *cmd, t_pipe *pipex, int expand);
char	*ft_getenv(char *var, t_pipe *pipex);

#endif
