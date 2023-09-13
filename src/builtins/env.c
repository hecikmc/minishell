/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:43 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:22:44 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Built-in env: Muestra por pantalla las variables de
 * entorno de minishell almacenadas en la estructura pipex (pipex->envp)
 * 
 * @param pipex struct donde se almacenan las variables de entorno del programa
 */
void	ft_env(t_pipe *pipex)
{
	int	i;

	i = 0;
	if (!pipex->envp)
		return ;
	while (pipex->envp[i])
	{
		ft_putstr_fd(pipex->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
