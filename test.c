#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

#define BUFFER_SIZE 3

char	*join(const char *s1, const char *s2)
{
	char	*result = malloc(strlen(s1) + strlen(s2) + 1);
	if (result)
	{
		strcpy(result, s1);
		strcat(result, s2);
	}
	return (result);
}

void	split(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
}

char *substr(char const *s, unsigned int start, size_t len)
{
	char *sub;
	int i;

	i = 0;
	if (!s)
		return (0);
	if (strlen(s) < start + len)
		len = strlen(s) - start;
	if (start >= strlen(s))
		return (strdup(""));
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	if (len < (strlen(s) - start))
	{
		while (len > 0)
		{
			sub[i++] = s[start++];
			len--;
		}
		sub[i] = '\0';
	}
	else
		sub = memcpy(sub, s + start, len);
	return (sub);
}

char	*get_next_line(int fd)
{
	char *str = NULL;
	char *temp ;
	static char *reste;
	int j;
	int ret;

	j = 0;
	str = malloc(BUFFER_SIZE + 1);
	if (!reste)
		reste = strdup("");
	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		str[ret] = '\0';
		j = 0;
		reste = join(reste, str);
		while (reste[j])
		{
			if (reste[j] == '\n')
			{
				temp = reste;
				reste = substr(reste, j + 1, strlen(reste + j));
				temp[j + 1] = '\0';
				return temp;
			}
			j++;
		}
	}
	if (ret == 0)
		return reste;
	return (reste);
}

int main()
{
	int fd;
	char *ligne;

	// OUVERTURE
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERREUR d'ouverture de fichier");
		return (1);
	}
	// LECTURE
	ligne = get_next_line(fd);
	printf("%s", ligne);
	ligne = get_next_line(fd);
	printf("%s", ligne);
	ligne = get_next_line(fd);
	printf("%s", ligne);
	ligne = get_next_line(fd);
	printf("%s", ligne);
	ligne = get_next_line(fd);
	printf("%s", ligne);
	ligne = get_next_line(fd);
	printf("%s", ligne);
	return (0);
}
