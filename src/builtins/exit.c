/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:46 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:22:47 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Verifica si los argumentos recibidos por el comando exit son
 * numericos. Si cumple con los requisitos devuelve el número introducido
 * en formato int, si no, muestra un error y devuelve -1. En caso de no 
 * introducir ningún argumento devuelve como salida 0.
 * 
 * @param cmd estructura con el comando introducido
 * @return int -1 si no es numerico, int con el numero introducido
 */
int	ft_checkexit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		while (cmd->args[1][i])
		{
			if (!ft_isdigit(cmd->args[1][i]))
			{
				err_msg("exit: numeric argument required: ");
				ft_putstr_fd(cmd->args[1], 2);
				ft_putstr_fd("\n", 2);
				return (-1);
			}
			i++;
		}
		return (ft_atoi(cmd->args[1]));
	}
	return (0);
}

/**
 * @brief Builtin 'exit', sale de la minishell. Sale con el valor 
 * que se le indique por argumentos. Si no se indica, sale con 0. 
 * 
 * @param cmd estructura con el comando
 */
void	ft_exit(t_cmd *cmd, t_pipe *pipex)
{
	pipex->shell_exit = ft_checkexit(cmd);
	if (cmd->args[1] && cmd->args[2])
	{
		err_msg("exit: too many arguments\n");
		return ;
	}
	if (pipex->shell_exit != -1)
	{
		free_pipe_structure(pipex);
		ft_free_cmds(cmd, pipex);
		exit(pipex->shell_exit);
	}
}
