/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:20 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/16 04:21:34 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



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
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	if (len < (ft_strlen(s) - start))
	{
		while (len > 0)
		{
			sub[i++] = s[start++];
			len--;
		}
		sub[i] = '\0';
	}
	else
		sub = ft_memcpy(sub, s + start, len);
	return (sub);
}

char	*get_next_line(int fd)
{
	char *str;
	char *temp ;
	static char *reste;
	int j;
	int ret;

	j = 0;
	str = malloc(BUFFER_SIZE + 1);
	if (!reste)
		reste = ft_strdup("");
	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		str[ret] = '\0';
		j = 0;
		reste = ft_strjoin(reste, str);
		while (reste[j])
		{
			if (reste[j] == '\n')
			{
				temp = reste;
				// printf("\n trmp : %s\n", temp);
				reste = substr(reste, j + 1, ft_strlen(reste + j));
				temp[j + 1] = '\0';
				return temp;
			}
			j++;
		}
	}
	free(str);
	// if (ret == 0)
	// 	return reste;
	// return (NULL);
	return (reste);
}

int main()
{
	int fd;
	char *ligne;
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
