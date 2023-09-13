/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:22 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/13 20:31:00 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Añade un string a un char ** al final del mismo. Si no existe, 
 * lo crea, si existe lo añade a la última posición.
 * 
 * @param str string a añadir
 * @param array char ** al que añadir 
 * @return char**
 */
char	**ft_addarray(char *str, char **array)
{
	char	**new_array;
	int		i;

	if (!array)
	{
		array = ft_calloc(sizeof(char *), 2);
		array[0] = str;
		return (array);
	}
	else
	{
		new_array = ft_calloc(sizeof(char *), ft_sizearray(array) + 2);
		i = -1;
		while (array[++i])
			new_array[i] = ft_strdup(array[i]);
		new_array[i] = ft_strdup(str);
		free_matrix(array);
		free(str);
		return (new_array);
	}
}

/**
 * @brief Elimina un elemento de un char **
 * 
 * @param pos int con la posición a eliminar
 * @param array char ** del que eliminar un elemento
 * @return char** sin ese elemento
 */
char	**ft_deleteitem(int pos, char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array || pos < 0 || pos > ft_sizearray(array))
		return (array);
	new_array = ft_calloc(sizeof(char *), ft_sizearray(array));
	while (array[i])
	{
		if (i >= pos)
			new_array[i] = ft_strdup(array[i + 1]);
		else
			new_array[i] = ft_strdup(array[i]);
		i++;
	}
	free_matrix(array);
	return (new_array);
}

/**
 * @brief Crea una copia de un char ** y devuelve la copia
 * 
 * @param array char ** a copiar
 * @return char** copiado en nueva dirección de memoria
 */
char	**ft_arraydup(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	new_array = ft_calloc(sizeof(char *), ft_sizearray(array) + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_array);
}

/**
 * @brief Función para medir un char **
 * 
 * @param array char **
 * @return int con el tamaño
 */
int	ft_sizearray(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Localiza la posición de una variable de entorno 
 * 
 * @param var string con el nombre de la variable
 * @param envp char ** con todas las variables
 * @return int posición donde se localiza, si no la localiza devuelve -1
 */
int	ft_foundenv(char *var, char **envp)
{
	int		i;
	char	*aux;

	i = 0;
	if (!var[0])
		return (-1);
	while (envp[i])
	{
		aux = ft_strchr(envp[i], '=') + 1;
		if (ft_strlen(var) == (size_t)(aux - envp[i] - 1))
			if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
				return (i);
		i++;
	}
	return (-1);
}
