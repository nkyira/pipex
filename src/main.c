/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jodavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:13:42 by jodavis           #+#    #+#             */
/*   Updated: 2025/04/04 10:13:14 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	t_data	*data;

	if (argc != 5)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	setup_data(data, argv, env);
	pid1 = fork();
	if (pid1 < 0)
		handle_error(data, "fork", data->pipefd[0], data->pipefd[1]);
	if (pid1 == 0)
		left_process(data);
	pid2 = fork();
	if (pid2 < 0)
		handle_error(data, "fork", data->pipefd[0], data->pipefd[1]);
	if (pid2 == 0)
		right_process(data);
	return (handle_exit(data, pid1, pid2));
}
