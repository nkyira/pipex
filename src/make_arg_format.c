/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   make_arg_format.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/04/04 09:41:57 by jodavis        #+#    #+#                */
/*   Updated: 2025/04/04 10:17:04 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*next_quote(char *cmd);

static char	*next_space(char *cmd)
{
	while (*cmd != ' ' && *cmd != 39 && *cmd)
		cmd++;
	if (*cmd == 39)
		cmd = next_quote(cmd);
	return (cmd);
}

static char	*next_quote(char *cmd)
{
	cmd++;
	while (*cmd != 39)
		cmd++;
	cmd++;
	if (*cmd == 39)
		cmd = next_quote(cmd);
	else if (*cmd != ' ')
		cmd = next_space(cmd);
	return (cmd);
}

static void	set_to(int *arg_format, int i, int value)
{
	arg_format[i] = value;
}

static int	*setup_arg_format(int len, char *cmd)
{
	int	*arg_format;

	arg_format = malloc(sizeof(int) * len);
	if (!arg_format)
		return (NULL);
	ft_bzero(arg_format, sizeof(int) * len);
	while (len--)
	{
		if (cmd[len] == 39)
			arg_format[len] = 3;
	}
	return (arg_format);
}

int	*make_arg_format(char *cmd)
{
	int		*arg_format;
	char	*start_ptr;

	arg_format = setup_arg_format(ft_strlen(cmd), cmd);
	if (!arg_format)
		return (NULL);
	start_ptr = cmd;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (!*cmd)
			break ;
		if (*cmd == 39)
		{
			set_to(arg_format, cmd - start_ptr + 1, 1);
			cmd = next_quote(cmd);
			set_to(arg_format, cmd - start_ptr - 1 - (*(cmd -1) == 39), 2);
		}
		else if (*cmd)
		{
			set_to(arg_format, cmd - start_ptr, 1);
			cmd = next_space(cmd);
			set_to(arg_format, cmd - start_ptr - 1 - (*(cmd -1) == 39), 2);
		}
	}
	return (arg_format);
}
