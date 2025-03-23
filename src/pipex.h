/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/24 15:42:32 by jodavis        #+#    #+#                */
/*   Updated: 2025/03/02 19:06:29 by jodavis        ########   odam.nl        */
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
char	**better_split(char *cmd);

#endif
