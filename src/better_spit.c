/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   better_spit.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/04/04 09:28:09 by jodavis        #+#    #+#                */
/*   Updated: 2025/04/04 10:19:06 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	do_stuff(char **arg, char **temp_arg, int len)
{
	*arg = malloc(len + 1);
	if (!arg)
		return (0);
	*temp_arg = *arg;
	(*arg)[len] = '\0';
	return (1);
}

static char	*fill_args(char **arg, char *cmd, char *tcmd, int **arg_format)
{
	int		len;
	char	*temp_arg;

	len = 1;
	while (**arg_format != 2)
	{
		if (*tcmd != 39)
			len++;
		(*arg_format)++;
		tcmd++;
	}
	if (*tcmd == 39)
		len--;
	if (!do_stuff(arg, &temp_arg, len))
		return (NULL);
	while (len--)
	{
		if (*cmd != 39)
			*(temp_arg++) = *cmd;
		else
			len++;
		cmd++;
	}
	return (tcmd);
}

//	ft_printf("arg_count = %d\n", arg_count);
//	ft_printf("%s\n", cmd);
//	while (++i < len)
//		ft_printf("%d", arg_format[i]);
//	ft_printf("\n");

char	**better_split(char *cmd)
{
	int		len;
	int		*arg_format;
	char	**args;
	int		i;

	len = ft_strlen(cmd);
	arg_format = make_arg_format(cmd);
	if (!arg_format)
		return (NULL);
	args = malloc(sizeof(char *) * (count_args(len, arg_format) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*cmd)
	{
		if (*arg_format == 1 || *arg_format == 2)
		{
			cmd = fill_args(&args[i++], cmd, cmd, &arg_format);
			if (!cmd)
				return ((char **)freesplit(args, i - 2));
		}
		cmd++;
		if (*cmd)
			arg_format++;
	}
	args[i] = NULL;
	return (args);
}
