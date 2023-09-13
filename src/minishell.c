/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmerchan <jmerchan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:23:58 by jmerchan          #+#    #+#             */
/*   Updated: 2023/09/08 19:57:27 by jmerchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_getline(t_pipe *pipex)
{
	char	*input;
	char	*aux;

	while (1)
	{
		ft_getpath(pipex);
		input = readline("\033[32;1m* \033[0mMiniShell $> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", pipex->fd_out);
			exit(0);
		}
		add_history(input);
		aux = ft_strtrim(input, " ");
		if (ft_strlen(input) > 0 && ft_strlen(aux) > 0)
			input = ft_checkpipe(input, pipex);
		else
			free(input);
		free(aux);
		free_matrix(pipex->path);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argv;
	pipex.fd_in = dup(0);
	pipex.tmp_out = dup(1);
	pipex.envp = ft_arraydup(envp);
	if (argc != 1)
		argc_error();
	printf("%s", (char *)&(HEADER));
	ft_getline(&pipex);
	exit(0);
}
