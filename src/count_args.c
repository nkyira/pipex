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

int	count_args(int len, int *arg_format)
{
	int	args;
	int	i;
	int	temp;

	args = 0;
	i = -1;
	while (++i < len)
	{
		if (arg_format[i] == 1)
		{
			i++;
			if (arg_format[i] != 3)
			{
				while (arg_format[i] != 2)
					i++;
				args++;
			}
			else
			{
				temp = i - 1;
				while (arg_format[i] == 3)
					i++;
				if (!arg_format[i])
				{
					args++;
					while (arg_format[i] != 2)
						i++;
				}
				else
				{
					arg_format[i] = 3;
					arg_format[temp] = 3;
				}
			}
		}
		else if (arg_format[i] == 2 && i == len - 1)
			args++;
		else if (arg_format[i] == 2 && arg_format[i + 1] == 1)
		{
			arg_format[i] = 3;
			i++;
			arg_format[i] = 3;
		}	
		else if (arg_format[i] == 2 && arg_format[i + 1] != 1)
			args++;
	}
	return (args);
}
