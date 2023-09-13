/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:48 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 18:18:26 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Built-in export: exporta a las variables de entorno (pipex)
 * la variable que se indique como parámetro. El parametro i es para
 * 
 * @param cmd struct con el comando y sus argumentos
 * @param pipex structu con las variables de entorno
 */
void	ft_export(t_cmd *cmd, t_pipe *pipex, int vsize)
{
	int		pos;
	char	*var_name;

	if (cmd->args[1] && ft_strchr(cmd->args[1], '='))
	{
		if (cmd->args[1][0] && (!ft_isalpha(cmd->args[1][0])
		&& cmd->args[1][0] != '_'))
		{
			err_msg("export: not a valid identifier\n");
			return ;
		}
		while (cmd->args[1][vsize] && cmd->args[1][vsize] != '=')
			vsize++;
		var_name = ft_substr(cmd->args[1], 0, vsize);
		pos = ft_foundenv(var_name, pipex->envp);
		if (pos < 0)
			pipex->envp = ft_addarray(ft_strdup(cmd->args[1]), pipex->envp);
		else
		{
			pipex->envp = ft_deleteitem(pos, pipex->envp);
			pipex->envp = ft_addarray(cmd->args[1], pipex->envp);
		}
		free(var_name);
	}
}
