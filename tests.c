#include <stdio.h>
#include "libft/libft.h"

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

char	*next_quote(char *cmd);

char	*next_space(char *cmd)
{
	while (*cmd != ' ' && *cmd != 39 && *cmd)
		cmd++;
	if (*cmd == 39)
		cmd = next_quote(cmd);
	return (cmd);
}

char	*next_quote(char *cmd)
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

void	set_to(int *arg_format, int i, int value)
{
	arg_format[i] = value;
}

int	*setup_arg_format(int len, char *cmd)
{
	int *arg_format;

	arg_format = malloc(sizeof(int) * len);
	ft_bzero(arg_format, sizeof(int) * len);
	while (len--)
	{
//		printf("cmd[len] = %c, len = %d\n", cmd[len], len);
		if (cmd[len] == 39)
			arg_format[len] = 3;
	}
	return (arg_format);;
}

int *count_args(char *cmd)
{
	int *arg_format;
	char *start_ptr;

	arg_format = setup_arg_format(ft_strlen(cmd), cmd);
	start_ptr = cmd;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (!*cmd)
			break;
		if (*cmd == 39)
		{
			set_to(arg_format, cmd-start_ptr + 1, 1);
			cmd = next_quote(cmd);
			set_to(arg_format, cmd-start_ptr - 1 - (*(cmd -1) == 39), 2);

		}
		else if (*cmd)
		{
			set_to(arg_format, cmd-start_ptr, 1);
			cmd = next_space(cmd);
			set_to(arg_format, cmd-start_ptr - 1 - (*(cmd -1) == 39), 2);
		}
	}
	return (arg_format);
}

void	fill_args(char **format, char *cmd, int arg_count)
{
	int i;
	int	l;
	int	quotes;

	i = 0;
	while(++i <= arg_count)
	{
		l = 0;
		quotes = 0;
		ft_printf("i = %d ", i);
		while (*cmd == ' ')
			cmd++;
		if (*cmd == 39)
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
		ft_printf("l = %d ", l);
		format[i] = malloc(sizeof(char) * (l + 1));
		ft_strlcpy(format[i], cmd, l + 1);
		ft_printf("format[i] = %s\n", format[i]);
		cmd = cmd + l + quotes;
	}
}

char	**better_split(char *cmd)
{
	int		q_count;
	int		arg_count;
	int		i;
	char	**format;

	i = 0;
	q_count = count_quotes(cmd);
	if (q_count < 2)
		return (ft_split(cmd, ' '));
	if (q_count % 2 == 1)
		exit(1);
	while (cmd[i] != ' ' && cmd[i])
	{
		i++;
	}
	if (!cmd[i])
	{
		format = malloc(sizeof(char *) * (i + 1));
		format[0] = ft_strdup(cmd);
		return (format);
	}
	ft_printf("arg_count = %d\n", arg_count);
	format = malloc(sizeof(char *) * (arg_count + 2));
	format[0] = malloc(sizeof(char) * (i + 1));
	format[arg_count + 2] = NULL;
	ft_printf("i = %d\n", i);
	ft_strlcpy(format[0], cmd, i + 1);
	fill_args(format, cmd + i + 1, arg_count);
	return (format);
}

int main(int argc, char **argv)
{
	(void)argc;
	int *arg_format = count_args(argv[1]);
	int i = -1;
	printf("%s\n", argv[1]);
	while (++i <= ft_strlen(argv[1]))
	{
		printf("%d", arg_format[i]);
	}
	printf("\n");

	return 0;
	char **format = better_split(argv[1]);
	while (*format)
	{
		ft_printf("format[i] = %s\n", *format);
		format++;
	}
}
