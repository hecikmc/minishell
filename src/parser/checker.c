/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:27 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:28 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Comprueba si está relleno el campo de comando en la estructura cmd.
 * cmd->cmd (char *). Escribe por pantalla error de comando no encontrado.
 * 
 * @param cmd estructura
 * @param pipex estructura con el número de comandos totales
 * @return int 0 si no existe, 1 si tiene algún valor.
 */
static int	ft_existcmd(t_cmd *cmd, t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmd)
	{
		if (!cmd[i].cmd)
		{
			err_msg_sintax("Command not found\n");
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Verifica que el input recibido tenga una sintaxis correcta de comillas,
 * redirecciones y pipes. Si hay error de sintaxis se guarda el error 258 en
 * la salida de la ejecución.
 * 
 * @param input string a verificar
 * @param pipex estructura necesaria para ejecutar los comandos
 * @return int 0 si todo está correcto, 1 si hay errores de sintaxis
 */
static int	ft_checkinput(char *input, t_pipe *pipex)
{
	if (ft_checkquotes(input) == 0 && ft_checksintaxpipex(input) == 0
		&& ft_checkredirect(input) == 0)
		return (0);
	else
	{
		pipex->shell_exit = 258;
		return (1);
	}
}

/**
 * @brief Verifica si hay un pipe '|' abierto y en tal caso se queda esperando
 * al siguiente comando hasta que el pipe esté cerrado o bien se encuentre un 
 * error de sintaxis, en tal caso mostraría error y devolvería el control al
 * usuario. 
 * 
 * @param input string con la entrada del usuario a chequear
 * @param pipex estruct pipe
 * @param split_pi char ** con el input separado por pipes |
 * @return char* input completo, con la union de todos los cmds
 */
static char	*ft_openpipe(char *input, t_pipe *pipex, char **split_pi)
{
	char	*aux;

	aux = NULL;
	if (ft_countpipe(input) + 1 != pipex->n_cmd)
	{
		while (ft_countpipe(input) + 1 != pipex->n_cmd)
		{
			aux = readline("pipe>");
			input = ft_strjoin_free(input, aux);
			free (aux);
			free_matrix(split_pi);
			if (ft_checkinput(input, pipex) == 1)
				return (input);
			split_pi = ft_split_shell(input, '|');
			split_pi = ft_cleanspaces(split_pi);
			pipex->n_cmd = ft_sizearray(split_pi);
		}
	}
	else
		free_matrix(split_pi);
	return (input);
}

/**
 * @brief Verifica si la entrada es correcta en cuanto a sintaxis 
 * (comillas cerradas, redirecciones correctamente escritas y 
 * pipes no consecutivos), si se ha quedado un pipe abierto se queda
 * esperando a recibir el siguiente comando. Verifica en cada entrada
 * si la sintaxis es correcta y devuelve la entrada si todo está correcto
 * para que se guarde en el historial de minishell. Una vez verificado
 * todo se procede a rellenar la estructura de comando y a ejecutar la sucesión
 * de comandos recibidos.
 * 
 * @param input string con la entrada del usuario
 * @param pipex struct con datos necesarios para la ejecución
 * @return char* string con el input para que se añada el historial de minishell
 */
char	*ft_checkpipe(char *input, t_pipe *pipex)
{
	char	**split_pi;
	t_cmd	*cmd;
	char	*new_input;

	if (ft_checkinput(input, pipex) == 0)
	{
		split_pi = ft_split_shell(input, '|');
		split_pi = ft_cleanspaces(split_pi);
		pipex->n_cmd = ft_sizearray(split_pi);
		input = ft_openpipe(input, pipex, split_pi);
		new_input = ft_expandit(input, pipex, 0);
		cmd = ft_getinput(new_input, pipex);
		free(new_input);
		if (ft_existcmd(cmd, pipex) == 1)
			child_generator(pipex, cmd);
	}
	else
		pipex->shell_exit = 258;
	return (input);
}
