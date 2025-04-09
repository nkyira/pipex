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

static void first_if(int *arg_format, char **cmd, char *start_ptr)
{
	set_to(arg_format, *cmd - start_ptr + 1, 1);
	*cmd = next_quote(*cmd);
	set_to(arg_format, *cmd - start_ptr - 1 - (*(*cmd -1) == 39), 2);
}

static void second_if(int *arg_format, char **cmd, char *start_ptr)
{
	set_to(arg_format, *cmd - start_ptr, 1);
	*cmd = next_space(*cmd);
	set_to(arg_format, *cmd - start_ptr - 1 - (*(*cmd -1) == 39), 2);
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
		while (ft_isspace(*cmd))
			cmd++;
		if (!*cmd)
			break ;
		if (*cmd == 39)
			first_if(arg_format, &cmd, start_ptr);
//		{
//			set_to(arg_format, cmd - start_ptr + 1, 1);
//			cmd = next_quote(cmd);
//			set_to(arg_format, cmd - start_ptr - 1 - (*(cmd -1) == 39), 2);
//		}
		else if (*cmd)
			second_if(arg_format, &cmd, start_ptr);
	}
	return (arg_format);
}
