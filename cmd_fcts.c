/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fcts.c                                          :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jodavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:56:14 by jodavis           #+#    #+#             */
/*   Updated: 2025/03/07 18:38:54 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	contains_space(char *s)
{
	while (*s)
	{
		if (*s == ' ')
			return (1);
		s++;
	}
	return (0);
}

int	end_dir(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ':')
	{
		i++;
	}
	return (i);
}

void	notfound_err(char *cmd, char **format)
{
	int		i;

	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	free(cmd);
	i = 0;
	while (format[++i])
		free(format[i]);
	free(format);
}

int	execute(char *cmd, char **env)
{
	char	**format;
	char	*temp;

	format = ft_split(cmd, ' ');
	if (access(format[0], X_OK) == 0)
	{
		execve(format[0], format, env);
		freesplit(format, tab_len(format));
		return (-1);
	}
	temp = format[0];
	format[0] = get_cmd_path(temp, env);
	if (!format[0])
	{
		notfound_err(temp, format);
		return (-1);
	}
	free(temp);
	execve(format[0], format, env);
	freesplit(format, tab_len(format));
	return (-1);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*dir;
	char	*temp;
	char	*paths;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			paths = env[i] + 5;
	i = 0;
	while (paths[i])
	{
		dir = ft_substr(paths + i, 0, end_dir(paths + i));
		temp = ft_strjoin(dir, "/");
		free(dir);
		dir = ft_strjoin(temp, cmd);
		free(temp);
		if (access(dir, X_OK) == 0)
			return (dir);
		i += end_dir(paths + i);
		free(dir);
		if (paths[i])
			i++;
	}
	return (NULL);
}
