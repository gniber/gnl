/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heloufra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 09:45:13 by heloufra          #+#    #+#             */
/*   Updated: 2022/01/07 12:19:39 by heloufra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*left[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!left[fd])
	{
		left[fd] = ft_calloc(1, sizeof(char));
		if (!left[fd])
			return (NULL);
	}
	buffer = get_line(fd, left[fd]);
	if (!buffer)
	{
		free(left[fd]);
		left[fd] = NULL;
		return (NULL);
	}
	free(left[fd]);
	line = pop_line(buffer, &left[fd]);
	free(buffer);
	return (line);
}

char	*get_line(int fd, char *left)
{
	char	*s;
	int		n;

	s = ft_substr(left, 0, ft_strlen(left));
	if (!s)
		return (NULL);
	while (!ft_strchr(s, '\n'))
	{
		n = extend_line(fd, &s);
		if (n == 0)
			break ;
		if (n < 0 || !s)
			return (NULL);
	}
	return (s);
}

int	extend_line(int fd, char **s)
{
	char	*buffer;
	char	*keeper;
	int		n;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (-1);
	n = read(fd, buffer, BUFFER_SIZE);
	if (n < 0)
	{
		free(*s);
		free(buffer);
		return (-1);
	}
	keeper = *s;
	*s = ft_strjoin(*s, buffer);
	free(keeper);
	free(buffer);
	if (n == 0 && **s == '\0')
	{
		free(*s);
		return (-1);
	}
	return (n);
}

char	*pop_line(char *buffer, char **left)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (!line)
		return (NULL);
	if (buffer[i])
		i++;
	*left = ft_substr(buffer, i, ft_strlen(&buffer[i]));
	if (!*left)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
