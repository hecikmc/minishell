/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:14 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/07 16:23:15 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Muestra por pantalla error al recibir parametros cuando
 * se ejecuta minishell.
 * 
 */
void	argc_error(void)
{
	printf("Structure: ./minishell\n");
	exit(1);
}

/**
 * @brief Muestra por pantalla el mensaje de error que recibe como argumento
 * 
 * @param str string con el mensaje de error 
 */
void	err_msg(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	ft_putstr_fd(str, 2);
}

/**
 * @brief Muestra por pantalla el mensaje de error que recibe como argumento
 * y realiza exit para finalizar el proceso que llamó a esta función.
 * 
 * @param str string con el mensaje de error
 */
void	err_msg_exit(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

/**
 * @brief Muestra por pantalla el mensaje de error que recibe como argumento
 * 
 * @param str string con el mensaje de error
 */
void	err_msg_sintax(char *str)
{
	ft_putstr_fd("\033[31;1m* \033[0mMiniShell: ", 2);
	ft_putstr_fd(str, 2);
}
