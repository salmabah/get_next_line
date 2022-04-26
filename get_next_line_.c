/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:00:03 by mel-amma          #+#    #+#             */
/*   Updated: 2022/04/26 02:43:14 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (ft_strdup(""));
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*createbuffer(int fd, char *readingbuffer, char *buffer)
{
	int		ret;
	char	*temp;

	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, readingbuffer, BUFFER_SIZE);
		if (ret == 0)
			return (buffer);
		else if (ret < 0)
			return (0);
		readingbuffer[ret] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		temp = buffer;
		buffer = ft_strjoin(temp, readingbuffer);
		free(temp);
		temp = 0;
		if (ft_strchr(readingbuffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*splittext(char *text)
{
	char	*buffer;
	int		i;

	i = 0;
	while (text[i] != '\n' && text[i])
		i++;
	buffer = substr(text, i + 1, ft_strlen(text));
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (0);
	}
	text[i + 1] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*readingbuffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	readingbuffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!readingbuffer)
		return (0);
	line = createbuffer(fd, readingbuffer, buffer);
	free(readingbuffer);
	readingbuffer = 0;
	if (!line)
		return (0);
	buffer = splittext(line);
	return (line);
}


int main()
{
	int fd;
	// OUVERTURE
	fd = open("test.txt", O_RDONLY);
	// fd = open("41_no_nl", O_RDWR);
	if (fd == -1)
	{
		printf("ERREUR d'ouverture de fichier");
		return (1);
	}
	// LECTURE
	// gnl(0, "01234567890123456789012345678901234567890\n")
	// fd = 0;
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
//est ce que je doit ajouter un retour a ligne dans la derniere ligne?
	return (0);
}