/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 21:06:19 by about             #+#    #+#             */
/*   Updated: 2023/11/25 15:43:50 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*get_after_line(char *src)
{
	size_t	i;
	char	*p;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	p = ft_str_dup(src + i);
	free(src);
	return (p);
}

static char	*get_line(char *line, int fd)
{
	char	*buf;
	int		i;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 1;
	while (!ft_str_chr(line, '\n') && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		buf[i] = '\0';
		if (line == NULL)
			line = ft_str_dup("");
		line = ft_str_join(line, buf);
	}
	free(buf);
	return (line);
}

static char	*set_line(char *src)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = NULL;
	if (!*src)
	{
		free(src);
		return (NULL);
	}
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i] && src[i] != '\n')
		dst[i] = src[i];
	if (src[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*next;
	char		*line;

	line = NULL;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
	{
		if (next)
			free(next);
		next = NULL;
		return (NULL);
	}
	next = get_line(next, fd);
	line = set_line(next);
	if (!line)
		next = NULL;
	next = get_after_line(next);
	return (line);
}
