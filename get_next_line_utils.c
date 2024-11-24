/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:40:17 by sechlahb          #+#    #+#             */
/*   Updated: 2024/11/24 20:58:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strchr( char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (NULL);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


int	ft_strlcat(char *dest, char *src, int n)
{
	int	i;
	int	destlen;
	int	srclen;

	destlen = ft_strlen((char *)dest);
	srclen = ft_strlen(src);
	if (n <= destlen)
		return (srclen + n);
	i = 0;
	while (src[i] && (destlen + i) < n - 1)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (srclen + destlen);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int				l;
	char			*str;

	l = 0;
    if (!s1)
	{
        s1 = ft_strdup("");
		if (!s1)
            return (NULL);
	}
    if (!s2)
	{
		free(s1);
    	return (NULL);
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(l + 1);
	if (!str)
		return (NULL);
	*str = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	return (free(s1),s1 = NULL, str);
}
