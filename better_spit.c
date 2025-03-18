#include "pipex.h"

int	count_quotes(char *cmd)
{
	int	count;

	count = 0;
	while(*cmd)
	{
		if (*cmd == 39)
			count++;
		cmd++;
	}
	return (count);
}

int count_args(char *cmd, int q_count, int start)
{
	int count;

	count = q_count / 2;
	cmd + start;
	while (*cmd && q_count)
	{
		if (*cmd == 39)
			q_count--;
		if (*cmd == 39 && *(cmd + 1) == 39)
		{
			count--;
			cmd++;
			q_count--;
		}
		cmd++;
	}
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd ++;
		if (*cmd)
			count++;
		while (*cmd != ' ' && *cmd)
			cmd++;
	}
	return (count);
}

void	fill_args(char **format, char *cmd, int arg_count)
{
	int i;
	int	l;
	int	quotes;

	i = 0
	while(++i <= arg_count)
	{
		l = 0
		quotes = 0;
		while (*cmd == ' ')
			cmd++;
		if (*cmd = 39)
		{
			cmd++;
			quotes++;
			while (cmd[l] != 39)
				l++;
		}
		else
		{
			while (cmd[l] != ' ' && cmd[l])
				l++;
		}
		format[i] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(format[i], cmd, l);
		cmd = cmd + 1 + quotes;
	}
}

char	**better_split(char *cmd)
{
	int		q_count;
	int		arg_count;
	int		i;
	char	**format[0];

	q_count = count_quotes(cmd);
	if (q_count < 2)
		return (ft_split(cmd, ' '));
	if (q_count % 2 == 1)
		exit(1);
	while (cmd[i] != ' ' && cmd[i])
		i++;
	if (!cmd[i])
	{
		format = malloc(sizeof(char *));
		format[0] = ft_strdup(cmd);
		return (format);
	}
	arg_count count_args(cmd, q_count, i);
	format = malloc(sizeof(char *) * arg_count + 2);
	format[0] = malloc(sizeof(char) * i + 1);
	format[arg_count + 1] = NULL;
	ft_strlcpy(format[0], cmd, i);
	fill_args(format, cmd + i + 1, arg_count);
	return (format)
}
