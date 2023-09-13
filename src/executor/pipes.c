/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:06 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 18:07:45 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child(t_cmd *cmd, t_pipe *pipex)
{
	char	*error;

	error = NULL;
	if (!cmd->cmd)
	{
		free_matrix(cmd->args);
		free(cmd->cmd);
		err_msg_exit(CMD_ERROR);
	}
	if (execve(cmd->cmd, cmd->args, pipex->envp) == -1)
	{
		error = ft_strjoin_free(cmd->cmd, ": ");
		error = ft_strjoin_free(error, CMD_ERROR);
		pipex->shell_exit = 127;
		err_msg(error);
	}
	exit (pipex->shell_exit);
}

static void	dup_assignation(t_pipe *pipex, t_cmd *cmd, int i)
{
	if (cmd->infile_redirect == 0)
	{
		dup2(pipex->fd_in, 0);
	}
	if (i != pipex->n_cmd - 1)
	{
		if (pipe(pipex->tube) == -1)
			err_msg(PIPE_ERROR);
		if (cmd->infile_redirect == 0)
			pipex->fd_in = pipex->tube[0];
		if (cmd->outfile_redirect == 0)
			pipex->fd_out = pipex->tube[1];
	}
	else if (cmd->outfile_redirect == 0)
		pipex->fd_out = dup(pipex->tmp_out);
	if (cmd->outfile_redirect == 0)
	{
		dup2(pipex->fd_out, 1);
		close(pipex->fd_out);
	}
}

static int	pipe_control(t_pipe *pipex, t_cmd *cmd, int i)
{
	pid_t	pid;
	int		to_wait;

	dup_assignation(pipex, &cmd[i], i);
	if (cmd[i].infile_redirect != 0 || cmd[i].outfile_redirect != 0)
		if (!redir_check(pipex, &cmd[i], i))
			return (0);
	if (builting(&cmd[i], pipex))
		return (1);
	pid = fork();
	if (!pid)
		child(&cmd[i], pipex);
	if (i == pipex->n_cmd - 1)
	{
		waitpid(pid, &to_wait, 0);
		pipex->shell_exit = WEXITSTATUS(to_wait);
	}
	return (2);
}

void	child_generator(t_pipe *pipex, t_cmd *cmd)
{
	int		i;
	int		nb_controler;
	int		keyboard_fd;
	int		display_fd;

	keyboard_fd = dup(0);
	display_fd = dup(1);
	i = -1;
	while (++i < pipex->n_cmd)
	{
		nb_controler = pipe_control(pipex, cmd, i);
		if (nb_controler == 0)
			break ;
		else if (nb_controler == 1)
			continue ;
	}
	dup2(keyboard_fd, 0);
	close(keyboard_fd);
	dup2(display_fd, 1);
	close(display_fd);
	ft_free_cmds(cmd, pipex);
}
