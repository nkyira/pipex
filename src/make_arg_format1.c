#include "pipex.h"

int		ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '\v')
		return (1);
	else if (c == '\f')
		return (1);
	else if (c == '\r')
		return (1);
	else
		return (0);
}

char	*next_space(char *cmd)
{
	while (!ft_isspace(*cmd) && *cmd != 39 && *cmd)
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
	else if (ft_isspace(*cmd))
		cmd = next_space(cmd);
	return (cmd);
}
