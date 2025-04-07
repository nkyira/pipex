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

static int	contains_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

static void	notfound_err(char *cmd, char **format)
{
	int		i;

	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	free(cmd);
	i = -1;
	while (format[++i])
		free(format[i]);
	free(format);
}

static int	hard_execute(char **format, char **env, char *cmd)
{
	if (access(format[0], X_OK) == 0)
	{
		execve(format[0], format, env);
		freesplit(format, tab_len(format));
		return (1);
	}
	freesplit(format, tab_len(format));
	perror(cmd);
	return (127);
}

int	execute(char *cmd, char **env)
{
	char	**format;
	char	*temp;

	format = better_split(cmd);
	if (!format)
		return (1);
	if (contains_slash(format[0]))
		return (hard_execute(format, env, cmd));
	temp = format[0];
	format[0] = get_cmd_path(temp, env);
	if (!format[0])
	{
		notfound_err(temp, format);
		return (127);
	}
	free(temp);
	execve(format[0], format, env);
	freesplit(format, tab_len(format));
	return (1);
}
