/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:20 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/20 03:32:26 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>


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
	char *nstr;
	int flag;

	flag = 0;
	j = 0;
	str = malloc(BUFFER_SIZE + 1);
	if (reste == NULL)
		reste = ft_strdup("");
	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		str[ret] = '\0';
		j = 0;
		// nstr = reste;
		// free(reste);
		reste = ft_strjoin(reste, str);
		while (reste[j])
		{
			// printf("\nreste[%d] = %c\n", j, reste[j]);
			if (reste[j] == '\n')
			{
				temp = reste;
				// printf("\n trmp : %s\n", temp);
				reste = substr(reste, j + 1, ft_strlen(reste + j + 1));
				// temp[j] = '\n';
				temp[j + 1] = '\0';
				// printf("\n%s", reste);
				return (temp);
			}
			flag = 1;
			j++;
		}
	}

	free(str);
		// reste = ft_strjoin(reste, str);
	j = 0;
	while (reste[j])
		{
			// printf("\nreste[%d] = %c\n", j, reste[j]);
			if (reste[j] == '\n')
			{
				// reste ="y\ntesttest" reste[0]='y' reste[1]='\n' temp="y\ntesttest" reste="testest" temp="y\n"
				temp = reste;
				reste = substr(reste, j + 1, ft_strlen(reste + j));
				// temp[j] = '\n';
				temp[j + 1] = '\0';
				return (temp);
			}
			flag = 1;
			j++;
		}
	// printf("\n%d %s\n", flag, reste);
	// if (flag == 1)
	// 	return (reste);
	// printf("%s", reste);
	if (j == ft_strlen(reste))
	{
		nstr = ft_strdup(reste);
		reste = NULL;
		return (nstr);
	}
	return (reste);
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
	printf("\n----\n%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	return (0);
}
