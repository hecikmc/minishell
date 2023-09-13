/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:29 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/08 19:26:32 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief En un string avanza el indice i si encuentra una comilla del 
 * tipo 'quote' hasta la siguiente exactamente igual.
 * 
 * @param str string sobre el que iterar
 * @param i puntero al indice del string
 * @param quote comilla ' o " (int ascii)
 * @return int 1 si encuentra comillas, 0 si en la posición i no hay comillas
 */
static int	ft_ignorequotes(char *str, int *i, int quote)
{
	if (str[*i] == quote && str[*i] != 0)
	{
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != quote)
			*i = *i + 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Recoge el último estado de ejecución del comando anterior 
 * (shell_exit), lo transforma a string y lo devuelve seguido de lo que 
 * 
 * @param var 
 * @param pipex 
 * @return char* 
 */
char	*ft_get_exit_status(char *var, t_pipe *pipex)
{
	char	*status;
	char	*subst;
	char	*joined;
	int		i;

	status = ft_itoa(pipex->shell_exit);
	i = 1;
	while (var[i] && var[i] != ' ' && var[i] != '\''
		&& var[i] != '"' && var[i] != '$')
		i++;
	subst = ft_substr(var, 1, i - 1);
	joined = ft_strjoin_free(status, subst);
	free(subst);
	return (joined);
}

/**
 * @brief Localiza y devuelve como string el valor de una variable de
 * entorno de la minishell. Si no se envia ninguna variable devuelve
 * un string vacio. Si se recibe $$ devuelve el pid de la minishell. 
 * Si recibe $? devuelve el estado de la última ejecución de comando.
 * 
 * @param var string con el nombre de la variable
 * @param pipex estructura con las variables de entorno
 * @return char* string con el valor de la variable
 */
char	*ft_getenv(char *var, t_pipe *pipex)
{
	int		i;
	char	*aux;
	int		size;

	i = 0;
	size = 0;
	if (!var[0])
		return (ft_strdup("$"));
	if (var[0] && var[0] == '?')
		return (ft_get_exit_status(var, pipex));
	while (var[size] != ' ' && var[size] != '\t' && var[size] != '\''
		&& var[size] != '"' && var[size] != '$' && var[size]
		&& var[size] != '|' && var[size] != '\'')
			size++;
	while (pipex->envp[i])
	{
		aux = ft_strchr(pipex->envp[i], '=') + 1;
		if (size == aux - pipex->envp[i] - 1)
			if (ft_strncmp(var, pipex->envp[i], size) == 0)
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}

/**
 * @brief avanza el indice de iteración del input hasta el final del nombre
 * de la variable. Devuelve string con el valor de la variable de entorno
 * encontrada en ese indice i.
 * 
 * @param i puntero al int indice que está iterando en el input
 * @param input string con el input recibido por el usuario
 * @param pipex estructura con las variables de entorno
 * @return char* valor de la variable encontrada
 */
char	*ft_expand_value(int *i, char *input, t_pipe *pipex)
{
	char	*aux;

	(*i)++;
	aux = ft_getenv(&input[*i], pipex);
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '$' && input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	(*i)--;
	return (aux);
}

/**
 * @brief Recibe la entrada de datos escrita por el usuario en minishell
 * comprueba si hay variables de entorno a expandir por su valor y devuelve
 * el input con el valor de las variables localizadas.
 * * Si la variable escrita está entre comillas simples, no se expande su valor.
 * * Si la variable escrita está entre comillas dobles, sí expande su valor.
 * * Si la variable no se encuentra entre comillas, sí expande su valor.
 * La función se llama de forma recursiva cuando encuentra una variable entre 
 * comillas dobles, en ese caso expande el valor enviando 1 a la propia función
 * para recibir el string entre comillado doble con las variables expandidas.
 * 
 * 
 * @param input string con la entrada del usuario a minishell
 * @param pipex estructura con las variables de entorno de minishell
 * @param expand 1 si hay que expandir, 0 si no hay que expandir
 * @return char* string con el resultado de expandir las variables en el input
 */
char	*ft_expandit(char *input, t_pipe *pipex, int expand)
{
	int		i;
	int		start;
	char	*result;
	char	*aux;

	i = -1;
	result = 0;
	while (input && input[++i])
	{
		start = i;
		if (expand == 0 && ft_ignorequotes(input, &i, '\'') == 1)
			aux = ft_substr(input, start, (i - start) + 1);
		else if (expand == 0 && ft_ignorequotes(input, &i, '"') == 1)
			aux = ft_expandit(ft_substr(input, start, (i - start) + 1),
					pipex, 1);
		else if (input[i] == '$')
			aux = ft_expand_value(&i, input, pipex);
		else
			aux = ft_substr(input, start, 1);
		result = ft_strjoin_free(result, aux);
		free(aux);
	}
	free(input);
	return (result);
}
