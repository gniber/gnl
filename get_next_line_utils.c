/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heloufra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:34:48 by heloufra          #+#    #+#             */
/*   Updated: 2022/01/07 12:01:38 by heloufra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!(char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_calloc(1, sizeof(char)));
	if (s_len < len)
		len = s_len;
	i = 0;
	while (s[i + start] && i < len)
		i++;
	p = malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	int		n;

	n = count * size;
	p = malloc(n);
	if (!p)
		return (NULL);
	while (n--)
	{
		((unsigned char *)p)[n] = 0;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	buffer;
	int		i;

	buffer = (ft_strlen(s1) + ft_strlen(s2) + 1);
	s = ft_calloc(buffer, sizeof(char));
	if (!s)
		return (s);
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
