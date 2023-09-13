/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:16 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 17:38:50 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Libera la memoria asignada a un char ** por completo
 * 
 * @param str char ** a liberar
 */
void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/**
 * @brief Libera la memoria asignada a cada elemento de la structura
 * que tiene una reserva de memoria.
 * 
 * @param cmd 
 */
void	free_cmd_structure(t_cmd *cmd)
{
	free_matrix(cmd->args);
	free(cmd->cmd);
	free(cmd->infile);
	free(cmd->outfile);
}

void	free_pipe_structure(t_pipe *pipex)
{
	free_matrix(pipex->envp);
	free_matrix(pipex->path);
}

void	ft_free_cmds(t_cmd *cmd, t_pipe *pipex)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (i < pipex->n_cmd)
		{
			free_cmd_structure(&cmd[i]);
			i++;
		}
		free(cmd);
		cmd = NULL;
	}
}
