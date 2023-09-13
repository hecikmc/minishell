/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:22:14 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:36:50 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief En función del caracter en el que nos encontremos en el string de 
 * entrada del usuario, se determina un estado actual, por defecto será WORD
 * cuando sea necesario recoger esa palabra como comando, argumento, fichero...
 * si encontramos un '>' cambiaremos el estado a RED_OUT o RED_APPEND dependiendo
 * de si es simple o doble '>'. Si encontramos '<' cambiará el estado a RED_IN
 * o RED_HERE dependiendo de si es simple o doble '<'.
 * 
 * @param current caracter en el que nos encontramos en la cadena de entrada
 * @param cmd estructura en la que tipificaremos la redirección 
 * (0 no hay, 1 simple, 2 doble)
 * @param status estado en el que nos encontrabamos anteriormente
 * @return t_typetoken estado actualizado
 */
t_typetoken	ft_redirectstatus(char current, t_cmd *cmd, t_typetoken status)
{
	if (current == '>')
	{
		cmd->outfile_redirect = 1;
		if (status == RED_OUT)
		{
			cmd->outfile_redirect = 2;
			status = RED_APPEND;
		}
		else
			status = RED_OUT;
	}
	else if (current == '<')
	{
		cmd->infile_redirect = 1;
		if (status == RED_IN)
			status = RED_HERE;
		else
			status = RED_IN;
	}
	return (status);
}

/**
 * @brief Se encarga de rellenar en la estructura cmd el nombre del comando
 * encontrado y los argumentos.
 * 
 * @param one_cmd string que contiene la entrada del usuario
 * @param i indice en el que nos encontramos en el input
 * @param pipex estructura con el path en el que localizar el cmd
 * con ruta absoluta
 * @param cmd estructura de comando en el que rellenar los campos comando
 * y argumentos
 */
static void	ft_fillcmd(char *one_cmd, int *i, t_pipe *pipex, t_cmd *cmd)
{
	if (!cmd->cmd)
	{
		cmd->cmd = ft_getname(&one_cmd[*i], i);
		cmd->args = ft_addarray(ft_strdup(cmd->cmd), cmd->args);
		cmd->cmd = ft_getcmd(*pipex, cmd->cmd);
	}
	else
	{
		cmd->args = ft_addarray(ft_getname(&one_cmd[*i], i), cmd->args);
	}
}

/**
 * @brief Se encarga de rellenar en el estruct cmd el nombre del fichero
 * correspondiente en función de si el redtype es para entrada o salida y 
 * dependiendo de si es simple o doble redirección.
 * 
 * @param one_cmd string con el input del usuario
 * @param i indice en el que iteramos en el input de usuario
 * @param cmd estruct en el que rellenar los datos de los ficheros cuando hay 
 * redirección
 * @param redtype estado que indica el tipo de redirección a rellenar 
 */
static void	ft_fillfile(char *one_cmd, int *i, t_cmd *cmd, t_typetoken redtype)
{
	if (redtype == RED_IN || redtype == RED_HERE)
	{
		if (cmd->infile && redtype == RED_IN)
			free(cmd->infile);
		cmd->infile = ft_getname(&one_cmd[*i], i);
		if (redtype == RED_HERE)
			ft_heredoc(cmd);
	}
	else if (redtype == RED_OUT || redtype == RED_APPEND)
	{
		if (!cmd->outfile)
			cmd->outfile = ft_getname(&one_cmd[*i], i);
		else
		{
			close(open(cmd->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644));
			free(cmd->outfile);
			cmd->outfile = ft_getname(&one_cmd[*i], i);
		}
	}
}

/**
 * @brief Se encarga de recorrer el input introducido por el usuario y 
 * rellenar la estructura cmd con los datos correspondientes en su campo
 * 
 * @param cmd estruct que contiene los datos del comando separados en variables
 * @param one_cmd string con el input del usuario (se recibe sin pipes)
 * @param pipex estruct que contiene el path para localizar la ruta absoluta
 * del comando
 */
static void	ft_getdatas(t_cmd *cmd, char *one_cmd, t_pipe *pipex)
{
	int			i;
	t_typetoken	status;

	i = 0;
	status = WORD;
	while (one_cmd[i])
	{
		status = ft_redirectstatus(one_cmd[i], cmd, status);
		if (one_cmd[i] != ' ' && one_cmd[i] != '\t' && one_cmd[i] != '<'
			&& one_cmd[i] != '>')
		{
			if (status == WORD)
				ft_fillcmd(one_cmd, &i, pipex, cmd);
			else
				ft_fillfile(one_cmd, &i, cmd, status);
			status = WORD;
		}
		i++;
	}
}

/**
 * @brief Recibe la entrada del usuario a ejecutar en minishell y recoge
 * en un array de cmd (comandos) los datos introducidos en la variable 
 * correspondiente.
 * 
 * 
 * @param input string con la entrada del usuario
 * @param pipex estructura con las variables de entorno 
 * @param cmd puntero a una estructura de comandos vacia
 * @return t_cmd* puntero de comandos 
 */
t_cmd	*ft_getinput(char *input, t_pipe *pipex)
{
	int		i;
	char	**split_pi;
	t_cmd	*cmd;

	i = 0;
	split_pi = ft_split_shell(input, '|');
	split_pi = ft_cleanspaces(split_pi);
	cmd = malloc(sizeof(t_cmd) * pipex->n_cmd);
	while (i < pipex->n_cmd)
	{
		cmd[i].infile_redirect = 0;
		cmd[i].outfile_redirect = 0;
		cmd[i].infile = NULL;
		cmd[i].outfile = NULL;
		cmd[i].args = NULL;
		cmd[i].cmd = NULL;
		ft_getdatas(&cmd[i], split_pi[i], pipex);
		i++;
	}
	free_matrix(split_pi);
	return (cmd);
}
