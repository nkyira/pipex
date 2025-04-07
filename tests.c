#include <stdio.h>
#include "libft/libft.h"

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
		if (cmd[len] == 39)
			arg_format[len] = 3;
	}
	return (arg_format);;
}

int *make_arg_format(char *cmd)
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

int count_args(int len, int *arg_format)
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
			args++;
			while (arg_format[i] != 2)
				i++;
		}
		else if (arg_format[i] == 2 && i == len - 1)
			args++;
		else if (arg_format[i] == 2 && arg_format[i + 1] == 1)
		{
			arg_format[i] = 1;
			i++;
			arg_format[i] = 2;
			args++;
		}	
		else
			args++;
	}
	return (args);
}

char	*fill_args(char **arg, char *cmd, char *temp_cmd,int **arg_format)
{
	int		len;
	char	*temp_arg;

	len = 1;
	while (**arg_format != 2)
	{
		if (*temp_cmd != 39)
			len++;
		(*arg_format)++;
		temp_cmd++;
	}
	if (*temp_cmd == 39)
		len--;
	*arg = malloc(len + 1);
	if (!arg)
		return (NULL);
	temp_arg = *arg;
	(*arg)[len] = '\0';
	while (len--)
	{
		if (*cmd != 39)
			*(temp_arg++) = *cmd;
		else
			len++;
		cmd++;
	}
	return (temp_cmd);
}


char	**better_split(char *cmd)
{
	int		arg_count;
	int		len;
	int		*arg_format;
	char	**args;
	int		i;

	len = ft_strlen(cmd);
	arg_format = make_arg_format(cmd);
	ft_printf("%s\n", cmd);
	i = -1;
	while (++i < len)
		ft_printf("%d", arg_format[i]);
	ft_printf("\n");
	arg_count = count_args(len, arg_format);
	ft_printf("arg_count = %d\n", arg_count);
	ft_printf("%s\n", cmd);
	i = -1;
	while (++i < len)
		ft_printf("%d", arg_format[i]);
	ft_printf("\n");
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	args[arg_count] = NULL;
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
	return (args);
}

int main(int argc, char **argv)
{
	(void)argc;
	char	**format;

	format = better_split(argv[1]);
	int i = 0;
	while (*format)
	{
		ft_printf("format[%d] = %s\n", i, *format);
		i++;
		format++;
	}
}
