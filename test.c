#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *join(const char* s1, const char* s2)
{
	char*	result = malloc(strlen(s1) + strlen(s2) + 1);

	if (result)
	{
		strcpy(result, s1);
		strcat(result, s2);
	}
	return (result);
}

void split(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
}



int main()
{
	int			fd;
	static char	*str = NULL;
	char		*temp;
	int			buffersize;
	char		*buf;
	int			j = 0;
	int			ret;

	buffersize = 3;

// OUVERTURE
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERREUR d'ouverture de fichier");
		return (1);
	}
// LECTURE

	str = malloc(buffersize + 1);
	while((ret = read(fd, str, buffersize)))
	{
		str[ret] = '\0';
		j = 0;
		while (str[j])
		{
			if (str[j] == '\n')
			{
				str[j] = '\0';
				buf = malloc(strlen(temp) + strlen(str));
				buf = join(temp, str);
				printf("\n****%s****\n", buf);
			}
			j++;
		}

		buf = malloc(strlen(str) + strlen(temp)  + 1);
		buf = join(temp, str);
		temp = buf;
	}

	return (0);
}
