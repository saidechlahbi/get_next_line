/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:41:35 by sechlahb          #+#    #+#             */
/*   Updated: 2024/11/24 20:35:49 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_last_rest_of_line(char *str)
{
    int i;
    char    *rest_of_line;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    rest_of_line = malloc(i + 2);
    if (!rest_of_line)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        rest_of_line[i] = str[i];
        i++;
    }
    rest_of_line[i] = '\n';
    rest_of_line[++i] = '\0';
    return (rest_of_line);
}

char *get_rest_for_next_line(char *str)
{
    int i;
    int j;
    int k;
    char    *buffer;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    k = i;
    j = 0;
    while (str[i++])
        j++;
    buffer = malloc(i - j + 2);
    if (!buffer)
        return (NULL);
    i = 0;
    while (str[k++])
        buffer[i++] = str[k];
    buffer[i] = '\0';
    return (free(str), buffer);
}
char *check_buffe(char *buffer, char **line)
{
    if (buffer == NULL)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if(!buffer)
            return (NULL);
    }
    else
    {
        *line = ft_strjoin(*line, buffer);
        buffer = malloc(BUFFER_SIZE + 1);
        if(!buffer)
            return (NULL);
    }
    return (buffer);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    int r;

    line = NULL;
    r = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = check_buffe(buffer, &line);
    while (1)
    {
        r = read (fd, buffer, BUFFER_SIZE);
        if (r <= 0)
          return (free(buffer),buffer = NULL, line);
        buffer[r] = '\0';
        if (ft_strchr(buffer, '\n') != NULL)
        {
            line = ft_strjoin(line, get_last_rest_of_line(buffer));
            buffer = get_rest_for_next_line(buffer);
            break;
        }
        else
            line = ft_strjoin(line, buffer);
    }
    return (line);
}

int main ()
{
    int fd;
    fd = open("formule.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    int i = 0;
   while (i < 12)
   {
    printf ("%s",get_next_line(fd));
    i++;
   }

}