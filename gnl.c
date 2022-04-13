
#include <stdio.h> // for std printf
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char *get_next_line(int fd)
{
    int     i = 0;
    char    c;
    char    *line;
    char    buffer[999999];

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer[i] = '\0';
    for (i = 0, c = 0; (read(fd, &c, 1) == 1); i++)
    {
        buffer[i] = c;
        buffer[i + 1] = '\0';
        if (buffer[i] == '\n')
            break;
    }
    if (buffer[0] == '\0')
        return NULL;
    line = malloc(i + 2);
    for (i = 0; buffer[i]; i++)
        line[i] = buffer[i];
    line[i] = '\0';
    return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	printf("%s", line);
	free(line);
	close(fd);
	// system("leaks a.out");
	
	return (0);
}