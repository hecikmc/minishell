/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:18 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:19 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Si la posición en la que se encuentra el indice i es una 
 * comilla doble o simple, avanza el indice i hasta la siguiente 
 * comilla exactamente igual. Si no encuentra comilla el indice no se
 * modifica. 
 * 
 * @param str string a localizar la comilla
 * @param i indice 
 * @return int 1 si encuentra una comilla, 0 si no
 */
int	ft_foundquotes(char *str, int *i)
{
	char	com;

	com = 0;
	if ((str[*i] == '\'' || str[*i] == '"') && str[*i] != 0)
	{
		com = str[*i];
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != com)
			*i = *i + 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Indica si hay una palabra en el string delimitada por el caracter s. 
 * Si encuentra una palabra avanza el indice i hasta el final de la palabra
 * 
 * @param str string a localizar la palabra
 * @param s char delimitador de la palabra
 * @param i indice del string
 * @return int 1 si localiza una palabra y 0 si no existe. (En la posición i)
 */
static int	ft_foundword(char *str, char s, int *i)
{
	if (str[*i] != s && str[*i] != 0)
	{
		while (str[*i] != 0 && str[*i] != s)
		{
			ft_foundquotes(str, i);
			*i = *i + 1;
		}
		return (1);
	}
	return (0);
}

/**
 * @brief Cuenta las palabras en un string separadas por el delimitador s
 * 
 * @param str string que contiene las palabras a contar
 * @param s char delimitador
 * @return int con el número de palabras localizadas
 */
static int	ft_cwords(char *str, char s)
{
	int	i;
	int	nwords;

	i = 0;
	nwords = 0;
	while (str[i])
	{
		while (str[i] == s && str[i] != 0)
			i++;
		if (str[i] != 0)
			nwords += ft_foundword(str, s, &i);
		if (str[i] != 0)
			ft_foundquotes(str, &i);
	}
	return (nwords);
}

/**
 * @brief Separa un string por "palabras" delimitadas con el caracter s, 
 * si localiza algo entre comillas (dobles o simples) lo toma todo como una 
 * palabra o parte de una palabra sin tener en cuenta los separadores que 
 * puedan existir entre esas comillas
 * 
 * @param str string a separar
 * @param s char delimitador
 * @return char** con el resultado de la separación
 */
char	**ft_split_shell(char *str, char s)
{
	int		i;
	int		is;
	int		len;
	char	**split;

	i = 0;
	is = 0;
	len = 0;
	split = ft_calloc(sizeof(char *), ft_cwords(str, s) + 1);
	if (!split)
		return (0);
	while (str[i])
	{
		while (str[i] == s && str[i] != 0)
		{
			len++;
			i++;
		}
		if (ft_foundword(str, s, &i))
		{
			split[is++] = ft_substr(str, len, i - len);
			len = i;
		}
	}
	return (split);
}
