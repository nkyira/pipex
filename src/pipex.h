/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/24 15:42:32 by jodavis        #+#    #+#                */
/*   Updated: 2025/04/04 09:47:59 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	char	**env;
	int		pipefd[2];
}	t_data;
int		execute(char *cmd, char **env);
char	*get_cmd_path(char *cmd, char **env);

//main functions
void	handle_error(t_data *data, char *str, int fd1, int fd2);
void	left_process(t_data *data);
void	right_process(t_data *data);
void	setup_data(t_data *data, char **argv, char **env);
int		handle_exit(t_data *data, pid_t pid1, pid_t pid2);
//better split functions
char	**better_split(char *cmd);
int		count_args(int len, int *arg_format);
int		*make_arg_format(char *cmd);

#endif
