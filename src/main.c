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

static void	left_process(t_data *data)
{
	int	filefd;

	close(data->pipefd[0]);
	if (access(data->infile, F_OK) < 0 || access(data->infile, R_OK) < 0)
	{
		perror(data->infile);
		free(data);
		exit(errno);
	}
	else
	{
		filefd = open(data->infile, O_RDONLY);
		dup2(filefd, STDIN_FILENO);
	}
	close(filefd);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[1]);
	execute(data->cmd1, data->env);
	free(data);
	exit(1);
}

static void	right_process(t_data *data)
{
	int	filefd;

	close(data->pipefd[1]);
	dup2(data->pipefd[0], STDIN_FILENO);
	close(data->pipefd[0]);
	filefd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(filefd, STDOUT_FILENO);
	close(filefd);
	execute(data->cmd2, data->env);
	free(data);
	exit(1);
}

static void	setup_data(t_data *data, char **argv, char **env)
{
	data->infile = argv[1];
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->outfile = argv[4];
	data->env = env;
	if (pipe(data->pipefd) == -1)
		exit(errno);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	t_data	*data;
	int		status1;
	int		status2;

	if (argc != 5)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	setup_data(data, argv, env);
	pid1 = fork();
	if (pid1 == 0)
		left_process(data);
	pid2 = fork();
	if (pid2 == 0)
		right_process(data);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	free(data);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}
