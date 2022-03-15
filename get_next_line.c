/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:48:37 by sbahraou          #+#    #+#             */
/*   Updated: 2022/03/15 23:48:31 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdlib.h>

char *spilt(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
	return (str);
}

char *cutbuffer(char **buffer, int *nb_bytes, int fd, int cnt)
{
	char	*ligne;
	char	*temp;
	int		i;

	// if (ft_strchr(buffer, '\n') == NULL)
	// {
	// 	ligne = ft_strdup("");
	// }
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	// ligne = ft_substr(buffer, 0, i);
	// if (i == BUF_SIZE)
	// {
		temp = *buffer;
		printf("cnt : %d", cnt);
		printf("\nold buffer : %s\n", temp);
		*buffer = malloc(BUF_SIZE * cnt);
		ligne = malloc(BUF_SIZE);
		if (ligne != NULL && buffer != NULL)
		{
			*nb_bytes = read(fd, ligne, BUF_SIZE);
			*buffer = ft_strjoin(temp, ligne);
			printf("\nnew buffer : %s\n", *buffer);
			// *nb_bytes = 0;
		}
		// buffer = malloc(strlen(temp) + BUF_SIZE);
		// buffer = ft_strjoin(temp, ligne);
	// }
	return (*buffer);
}

char	*get_next_line(int fd)
{
	int		resultat;
	char	*buffer;
	char	*ligne;
	int		nb_bytes;
	int		cnt;

	cnt = 1;
	if ((buffer = (char *)malloc(sizeof(char) * BUF_SIZE + 1)) == NULL)
		return (NULL);
    nb_bytes = read(fd, buffer, BUF_SIZE);
	printf("\n%s %d", buffer, nb_bytes);
	while (nb_bytes > 0)
	{
		cnt++;
		ligne = cutbuffer(buffer, &nb_bytes, fd, cnt);
	}
	return (ligne);
}

int main()
{
	FILE	*f;
	int		fd;
	// char	*line;

	f = fopen("test.txt", "r");
	fd = fileno(f);
	// line = get_next_line(fd);
	printf("%s", get_next_line(fd));
	return (0);
}

// int main()
// {
// 	char ligne[25] = "Salma bahraoui";
// 	printf("%s\n", ligne);
// 	ligne[5]='\0';
// 	printf("%s", ligne);
// 	int i = 0;
// 	char str[4] = {'b','o','n', '\0'};
// 	printf("%s", str);
// 	while (str[i] != '\0')
// 		i++;
// 	printf("%d", i);
// 	return (0);
// }
// int	main()
// {
// 	char	buf[BUF_SIZE];
// 	ssize_t	octet_lus;
// 	int		fd;
// 	// char	*buf;
// 	fd = open("test.txt", O_RDONLY);

// 	printf("le nombre d'octets : %d\tfile descriptor : %d", BUF_SIZE, fd);
// 	if (fd == -1)
// 	{
// 		printf("erreur");
// 		return (1);
// 	}
// 	// octet_lus = read(fd, buf, noctets);
// 	// buf = malloc(BUF_SIZE);
// 	while ((octet_lus = read(fd, buf, noctets)) > 0)
// 	{
// 		printf("%s", strchr(buf, '\n'));
// 	}
// 	buf[octet_lus] = '\0';
// 	printf("\n%s\noctets lus : %zd", buf, octet_lus);
// 	return (0);
// }
