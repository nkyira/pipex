/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   count_args.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/04/04 09:35:16 by jodavis        #+#    #+#                */
/*   Updated: 2025/04/04 09:49:15 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	normspaghetti(int *i, int *arg_format, int *args)
{
	arg_format[*i] = 1;
	(*i)++;
	arg_format[*i] = 2;
	(*args)++;
}

int	count_args(int len, int *arg_format)
{
	int	args;
	int	i;

	args = 0;
	i = -1;
	while (++i < len)
	{
		if (arg_format[i] == 1)
		{
			while (arg_format[i] != 2)
				i++;
			args++;
		}
		else if (arg_format[i] == 2 && i == len - 1)
			args++;
		else if (arg_format[i] == 2 && arg_format[i + 1] == 1)
			normspaghetti(&i, arg_format, &args);
		else
			args++;
	}
	return (args);
}
