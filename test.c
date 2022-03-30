#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *join(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1);

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
}

char *split(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
	return (str);
}

int main()
{
    int fd;
    static char *str = NULL;
    char *temp;
    int buffersize;
    char *buf;
    int i =1;
    int j = 0;


    buffersize = 10;

// OUVERTURE
    fd = open("test.txt", O_RDONLY);
// LECTURE
    str = malloc(11);
    while(read(fd, str, 10))
    {
        while (str[j++])
            if (str[j] == '\n')
                str = split(str);

        buf = malloc(buffersize + strlen(str) *i);
        buf = join(temp, str);
        temp = buf;
        i++;
        printf("%s\n", buf);
    }
        
    return (0);
}