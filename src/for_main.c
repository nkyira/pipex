#include "pipex.h"

void	handle_error(t_data *data, char *str, int fd1, int fd2)
{
	perror(str);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	free(data);
	exit(errno);
}

void	left_process(t_data *data)
{
	int	filefd;
	int	return_value;

	close(data->pipefd[0]);
	filefd = open(data->infile, O_RDONLY);
	if (filefd < 0)
			handle_error(data, data->infile, data->pipefd[1], -1);
	if (dup2(filefd, STDIN_FILENO) < 0)
			handle_error(data, "dup2", data->pipefd[1], filefd);
	close(filefd);
	if(dup2(data->pipefd[1], STDOUT_FILENO) < 0)
			handle_error(data, "dup2", data->pipefd[1], -1);
	close(data->pipefd[1]);
	return_value = execute(data->cmd1, data->env);
	free(data);
	exit(return_value);
}

void	right_process(t_data *data)
{
	int	filefd;
	int	return_value;

	close(data->pipefd[1]);
	if(dup2(data->pipefd[0], STDIN_FILENO) < 0)
			handle_error(data, "dup2", data->pipefd[0], -1);
	close(data->pipefd[0]);
	filefd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
			handle_error(data, data->outfile, -1, -1);
	if(dup2(filefd, STDOUT_FILENO) < 0)
			handle_error(data, "dup2", filefd, -1);
	close(filefd);
	return_value = execute(data->cmd2, data->env);
	free(data);
	exit(return_value);
}

void	setup_data(t_data *data, char **argv, char **env)
{
	data->infile = argv[1];
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->outfile = argv[4];
	data->env = env;
	if (pipe(data->pipefd) == -1)
	{
		perror("pipe");
		free(data);
		exit(errno);
	}
}

int	handle_exit(t_data *data, pid_t pid1, pid_t pid2)
{
	int		status1;
	int		status2;

	close(data->pipefd[0]);
	close(data->pipefd[1]);
	free(data);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}
