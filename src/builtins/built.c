/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:28 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 18:13:24 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Pasa a minúscula todos los caracteres de un string
 * 
 * @param str char *
 */
static void	to_lower(char *str)
{	
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_tolower(str[i]);
	}
}

/**
 * @brief Función que comprueba si el comando es un builting para derivarlo
 * a la correspondiente función si así lo es
 * 
 * @param cmd estructura de comando
 * @param pipex estructura con las variables de entorno, tuberias...
 * @return int 1 si es un builting y 0 si no lo es
 */
int	builting(t_cmd *cmd, t_pipe *pipex)
{
	to_lower(cmd->args[0]);
	if (!ft_strncmp(cmd->args[0], "echo", 5)
		|| !ft_strncmp(cmd->args[0], "/bin/echo", 10))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd, pipex);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd, pipex, 0);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd, pipex);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(pipex);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd, pipex);
	else
		return (0);
	pipex->shell_exit = 0;
	return (1);
}
