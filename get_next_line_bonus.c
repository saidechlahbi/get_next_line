/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:41:35 by sechlahb          #+#    #+#             */
/*   Updated: 2024/11/28 00:40:46 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = malloc(size * nmemb);
	if (!s)
		return (NULL);
	while (i < size * nmemb)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

static char	*get_full_line(int fd, char *buffer)
{
	char	*full_line;
	char	*vessel;
	ssize_t	r;
	char	*s;

	r = 0;
	full_line = ft_strdup(buffer);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	while (!ft_strchr(full_line, '\n'))
	{
		vessel = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!vessel)
			return (free(full_line), NULL);
		r = read(fd, vessel, BUFFER_SIZE);
		if (r == 0)
			return (free(vessel), full_line);
		else if (r < 0)
			return (free(full_line), free(vessel), NULL);
		s = full_line;
		full_line = ft_strjoin(full_line, vessel);
		free(s);
		free(vessel);
	}
	return (full_line);
}

static char	*get_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	line = ft_calloc(i + 2, 1);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*get_rest_of_line(char *str)
{
	char	*rest;

	while (*str && *str != '\n')
		str++;
	if (*(++str) == '\0')
		return (NULL);
	rest = ft_strdup(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*full_line;

	full_line = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	if (!buffer[fd])
		return (NULL);
	full_line = get_full_line(fd, buffer[fd]);
	free(buffer[fd]);
	if (!full_line)
		return (NULL);
	line = get_line(full_line);
	if (!line)
		return (NULL);
	buffer[fd] = get_rest_of_line(full_line);
	free(full_line);
	return (line);
}

// int	main(void)
// {
// 	int fd = 0; // Assuming 0 is a valid file descriptor (stdin)
// 	char *line;
// 	fd = open("formule.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	int fd1 = open("formule1.txt", O_RDONLY);
// 	if (fd1 == -1)
// 		return (1);

// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("%s",line);
// 	// 	free(line);
// 	// }
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}

// 	while (line = get_next_line(fd1))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }