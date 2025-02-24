#include "pipex.h"

extern char **environ;

int main(int argc, char **argv)
{
	int i;

	if (argc != 5)
		return (0);
	if(access(argv[1], F_OK) < 0)
		perror(argv[1]);
	else if(access(argv[1], R_OK) < 0)
		perror(argv[1]);
	i = -1;
	while (environ[++i])
		ft_printf("environ[%d] = %s\n", i, environ[i]);
}
