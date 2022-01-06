/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heloufra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:27:19 by heloufra          #+#    #+#             */
/*   Updated: 2022/01/06 18:57:27 by heloufra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*tracer;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tracer)
		tracer = ft_calloc(1, sizeof(char));
	if (ft_strchr(tracer, '\n'))
	{
		buffer = tracer;
		return (pop_line(buffer, &tracer));
	}
	buffer = get_line(fd, &tracer);
	if (!buffer)
		return (NULL);
	return (pop_line(buffer, &tracer));
}

char	*get_line(int fd, char **tracer)
{
	char	*string;
	int		n;

	n = 1;
	string = ft_substr(tracer, 0, ft_strlen(*tracer));
	if (!string)
		return (NULL);
	while (ft_strchr(string, '\n') == NULL && n)
	{
		n = extend_string(fd, &string);
		if (n < 0)
			return (NULL);
	}
	if (n == 0)
	{
		free(*tracer);
		*tracer == NULL;
	}
	return (string);
}

int	extend_string(int fd, char **string)
{
	int		n;
	char	*substring;
	char	*holder;

	substring = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!substring)
	{
		free(*string);
		return (-1);
	}
	n = read(fd, substring, BUFFER_SIZE);
	if (n < 0)
	{
		free(*string);
		free(substring);
		return (-1);
	}
	holder = *string;
	*string = ft_strjoin(*string, substring);
	free(holder);
	free(substring);
	return (n);
}

char	*pop_line(char *buffer, char **tracer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (buffer[i])
		i++;
	if (*tracer)
		*tracer = ft_substr(buffer, i, ft_strlen(&buffer[i]));
	free(buffer);
	return (line);
}

