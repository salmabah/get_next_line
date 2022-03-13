/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:48:37 by sbahraou          #+#    #+#             */
/*   Updated: 2022/03/13 22:56:12 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdlib.h>

char *cutbuffer(char *buffer, int *nb_bytes)
{
	char	*ligne;
	int		i;

	// if (ft_strchr(buffer, '\n') == NULL)
	// {
	// 	ligne = ft_strdup("");
	// }

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;

	ligne = ft_substr(buffer, 0, i);
	return (ligne);
}

char    *get_next_line(int fd)
{
	int		resultat;
	char	*buffer;
	char	*ligne;
	int		nb_bytes;

	buffer = (char *)malloc(sizeof(char) * BUF_SIZE + 1);
    nb_bytes = read(fd, buffer, BUF_SIZE);
	printf("%s %d", buffer, nb_bytes);
	while (nb_bytes > 0)
	{
		ligne = cutbuffer(buffer, &nb_bytes);
	}
    return (ligne);
}

int main()
{
	FILE	*f;
	int		fd;
	char	*line;

	f = fopen("test.txt", "r");
	fd = fileno(f);
	printf("%d", fd);
	line = get_next_line(fd);
	// printf("%s", line);
	return (0);
}

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
