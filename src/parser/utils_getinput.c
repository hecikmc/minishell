/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getinput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:42 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:43 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Cuando se detecta heredoc en el input del usuario, se queda esperando
 * la entrada de datos del usuario hasta que introduzca la palabra clave. 
 * Guarda el input del usuario en un fichero temporal en la carpeta temporal del 
 * sistema para posteriormente utilizarlo como infile en el comando introducido
 * 
 * @param cmd estructura con el comando introducido
 */
void	ft_heredoc(t_cmd *cmd)
{
	int		tmp_fd;
	char	*input;

	tmp_fd = open(HEREDOC_FILE, O_TRUNC | O_CREAT | O_RDWR, 0644);
	input = readline("> ");
	while (input && ft_strncmp(input, cmd->infile, ft_strlen(cmd->infile) + 1))
	{
		write(tmp_fd, input, ft_strlen(input));
		write(tmp_fd, "\n", 1);
		input = readline("> ");
	}
	close(tmp_fd);
	free(cmd->infile);
	cmd->infile = ft_strdup(HEREDOC_FILE);
}

/**
 * @brief Recoge un string que forma parte de una misma "palabra", bien sea
 * el nombre de un fichero, de un comando o un argumento. Avanza el indice j
 * hasta el final de la palabra.
 * 
 * @param cmd string con el comando introducido
 * @param j indice por el que se está iterando en el string
 * @return char* string con la palabra recogida (comando, argumento, fichero)
 */
char	*ft_getname(char *cmd, int *j)
{
	int		i;
	int		start;
	char	*name;
	char	*aux;

	i = 0;
	name = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>')
	{
		start = i;
		if (ft_foundquotes(cmd, &i))
			aux = ft_substr(cmd, start + 1, (i - start) - 1);
		else
			aux = ft_substr(cmd, start, 1);
		name = ft_strjoin_free(name, aux);
		free(aux);
		i++;
	}
	*j += i - 1;
	return (name);
}
