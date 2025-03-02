/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fcts.c                                          :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jodavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:56:14 by jodavis           #+#    #+#             */
/*   Updated: 2025/03/02 19:13:26 by jodavis        ########   odam.nl        */
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

int	execute(char *cmd, char **env)
{
	char	**format;
	char	*temp;

	format = ft_split(cmd, ' ');
	temp = format[0];
	format[0] = get_cmd_path(temp, env);
	free(temp);
	if (execve(format[0], format, env) < 0)
		return (-1);
	return (0);
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
