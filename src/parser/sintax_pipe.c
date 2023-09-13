/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:35 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:36 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Comprueba que en una entrada no existan pipes '|' consecutivos
 * 
 * @param input char * que comprobar
 * @return int 0 si no existe consecución y 1 si existe
 */
static int	ft_consecutivepipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input[i] == '|')
		{
			i++;
			ft_foundquotes(input, &i);
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				ft_foundquotes(input, &i);
				i++;
			}
			if (input[i] && input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief función para contar el número de '|' (pipes) en un string, 
 * sin tener en cuenta los que están entre comillas (dobles o simples)
 * 
 * @param input char *
 * @return int con el número de | localizados
 */
int	ft_countpipe(char *input)
{
	int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	while (input[i])
	{
		ft_foundquotes(input, &i);
		if (input[i] == '|')
			npipe++;
		i++;
	}
	return (npipe);
}

/**
 * @brief Verifica que el número de pipes sea uno menos que el número total 
 * de comandos recibidos, que el primer caracter no sea un pipe y que no 
 * existan pipes consecutivos. Si hay error muestra mensaje de error por pantalla
 * 
 * @param input string que hay que verificar
 * @param split_pi input spliteado por '|'
 * @return int 1 si hay error, 0 si está todo correcto
 */
static int	ft_checkn_pipes(char *input, char **split_pi)
{
	if (ft_countpipe(input) > ft_sizearray(split_pi) || input[0] == '|'
		|| ft_consecutivepipes(input) == 1)
	{
		err_msg_sintax("Syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Verifica si la sintaxis de pipes '|' sea correcta, que no existan
 * pipes consecutivos, que no exista pipe abierto y que delante y detras de cada
 * pipe exista un comando. Escribe por pantalla mensaje de error de sintaxis.
 * 
 * @param input char * que se va a verificar
 * @return int 0 si está todo correcto, 1 si no está correcto
 */
int	ft_checksintaxpipex(char *input)
{
	int		i;
	int		r;
	char	**split;

	i = -1;
	r = 0;
	split = ft_split_shell(input, '|');
	split = ft_cleanspaces(split);
	r = ft_checkn_pipes(input, split);
	if (ft_countpipe(input) != ft_sizearray(split) - 1 && r == 0)
	{
		while (split[++i])
		{
			if (ft_strlen(split[i]) == 0)
			{
				err_msg_sintax("Syntax error near unexpected token `|'\n");
				r = 1;
			}
		}
	}
	free_matrix(split);
	return (r);
}
