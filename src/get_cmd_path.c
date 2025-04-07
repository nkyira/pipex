#include "pipex.h"

static int	end_dir(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ':')
	{
		i++;
	}
	return (i);
}
char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*dir;
	char	*temp;
	char	*paths;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			paths = env[i] + 5;
	i = 0;
	while (paths[i])
	{
		dir = ft_substr(paths + i, 0, end_dir(paths + i));
		temp = ft_strjoin(dir, "/");
		free(dir);
		dir = ft_strjoin(temp, cmd);
		free(temp);
		if (access(dir, X_OK) == 0)
			return (dir);
		i += end_dir(paths + i);
		free(dir);
		if (paths[i])
			i++;
	}
	return (NULL);
}
