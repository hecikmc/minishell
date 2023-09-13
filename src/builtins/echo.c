/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:40 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:22:41 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Built-in echo: imprime por pantalla lo que reciba por argumentos
 * 
 * @param cmd struct con el comando a ejecutar y sus argumentos
 */
void	ft_echo(t_cmd *cmd)
{
	int	j;

	j = 1;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
		j++;
	while (cmd->args[j])
	{
		ft_putstr_fd(cmd->args[j++], 1);
		if (cmd->args[j])
			ft_putstr_fd(" ", 1);
	}
	if (!(cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0))
		ft_putstr_fd("\n", 1);
}
