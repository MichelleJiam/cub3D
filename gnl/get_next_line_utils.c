/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 18:31:06 by mjiam         #+#    #+#                 */
/*   Updated: 2020/05/01 16:30:39 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlentoc(char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

char	*ft_strndup(char *s1, size_t len)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = malloc(sizeof(*s1) * (len + 1));
	if (!s2)
		return (0);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*newstr;

	i = 0;
	if (!s1)
		return (0);
	len = ft_strlentoc(s1, '\0') + ft_strlentoc(s2, '\0');
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (0);
	while (*s1)
	{
		newstr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		newstr[i] = *s2;
		i++;
		s2++;
	}
	newstr[i] = '\0';
	return (newstr);
}

int		makeline(char **line, char **temp, char c)
{
	char	*str1;
	size_t	len;
	size_t	origlen;

	str1 = NULL;
	if (!*temp)
		return (-1);
	origlen = 0;
	len = ft_strlentoc(*temp, c);
	str1 = ft_strndup(*temp, len);
	if (!str1)
		return (-1);
	origlen = ft_strlentoc(*temp, '\0');
	if (len + 1 < origlen)
		ft_memcpy(*temp, (*temp + len + 1), (origlen - len));
	else
	{
		free(*temp);
		*temp = NULL;
	}
	*line = str1;
	return (c == '\n' ? 1 : 0);
}

int		maketemp(char **temp, char *readbuf)
{
	char	*newtemp;

	newtemp = NULL;
	if (!readbuf)
		return (-1);
	if (*temp)
		newtemp = ft_strjoin(*temp, readbuf);
	else
		newtemp = ft_strndup(readbuf, ft_strlentoc(readbuf, '\0'));
	if (!newtemp)
		return (-1);
	free(*temp);
	*temp = newtemp;
	return (0);
}
