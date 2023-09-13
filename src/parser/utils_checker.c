/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:39 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:47 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Función que elimina ' ' (espacios) (si los hubiera), 
 * al comienzo y al final del string, recibe un char ** ,va liberando
 * cada item y lo sustituye por el nuevo string sin espacios.
 * 
 * @param split char **
 * @return char** 
 */
char	**ft_cleanspaces(char **split)
{
	int		i;
	char	*trim;

	i = 0;
	while (split[i])
	{
		trim = ft_strtrim(split[i], " ");
		free(split[i]);
		split[i] = trim;
		i++;
	}
	return (split);
}

/**
 * @brief Función que recoge la variable de entorno PATH del programa
 * y la guarda en la estructura pipex (pipex->path como char **) Se recoge
 * cada vez que se ejecuta una nueva entrada ya que ha podido ser eliminada
 * de las variables de entorno y en ese caso pipex->path = NULL.
 * 
 * @param pipex struct que almacena las variablse de entorno y recoge el PATH
 */
void	ft_getpath(t_pipe *pipex)
{
	int		i;

	i = 0;
	while (pipex->envp[i] && ft_strnstr(pipex->envp[i], "PATH=", 5) == 0)
		i++;
	if (i == ft_sizearray(pipex->envp))
		pipex->path = 0;
	else
		pipex->path = ft_split(pipex->envp[i] + 5, ':');
}

/**
 * @brief Recoge el comando con la ruta completa buscando en pipex->path
 * si se puede ejecutar el comando recogido (cmd)
 * 
 * @param pipex struct que contiene el path con las rutas de los ejecutables
 * @param cmd string comando
 * @return char* comando con la ruta absoluta 
 */
char	*ft_getcmd(t_pipe pipex, char *cmd)
{
	int		i;
	char	*aux;
	char	*c;
	char	*ex;

	i = 0;
	while (cmd[i] != 0 && cmd[i] != ' ')
		i++;
	ex = ft_substr(cmd, 0, i);
	i = 0;
	if (access(ex, X_OK) == 0)
		return (free(cmd), ex);
	while (pipex.path && pipex.path[i])
	{
		aux = ft_strjoin(pipex.path[i], "/");
		c = ft_strjoin(aux, ex);
		free (aux);
		if (access(c, X_OK) == 0)
			return (free (ex), free(cmd), c);
		free (c);
		i++;
	}
	free (ex);
	return (cmd);
}

/**
 * @brief Verifica si tanto comillas simples como comillas
dobles están cerradas en un string, sin tener en cuenta las comillas que puedan 
estar entre comilladas ya que estas sí pueden estar abiertas.
 * 
 * @param quotes string
 * @return Devuelve 0 si no están cerradas y 1 si lo están.
 */
static int	ft_checkclose(char *quotes)
{
	int	i;
	int	com;

	i = 0;
	while (quotes[i])
	{
		if (quotes[i] == 39 || quotes[i] == '"')
		{
			com = quotes[i];
			ft_foundquotes(quotes, &i);
			if (quotes[i] != com)
				return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Verifica si tanto comillas simples como comillas dobles
 * están cerradas en un string, sin tener en cuenta las comillas
 * que puedan estar entre comilladas ya que estas sí pueden estar abiertas.
 * 
 * @param input char *
 * @return int 
 */
int	ft_checkquotes(char *input)
{
	char	**quotes;
	int		i;

	i = 0;
	quotes = ft_split_shell(input, ' ');
	while (quotes[i])
	{
		if (ft_strchr(quotes[i], '\'') || ft_strchr(quotes[i], '"'))
		{
			if (ft_checkclose(quotes[i]) == 0)
			{
				err_msg_sintax("Syntax error: ' or \" must be closed\n");
				free_matrix(quotes);
				return (1);
			}
		}
		i++;
	}
	free_matrix(quotes);
	return (0);
}
