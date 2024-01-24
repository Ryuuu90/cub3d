/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 21:12:22 by about             #+#    #+#             */
/*   Updated: 2023/11/25 14:37:43 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_str_chr(char *s, int c)
{
	unsigned char	p;
	size_t			i;

	p = (unsigned char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != p)
	{
		i++;
	}
	if (s[i] == p)
	{
		return (s + i);
	}
	return (NULL);
}

char	*ft_str_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc(sizeof(char) * (i + j + 1));
	if (!p)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		p[i] = s1[i];
	while (s2[j] != '\0')
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	free (s1);
	return (p);
}

char	*ft_str_dup(char *s1)
{
	size_t	i;
	char	*p;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	p = malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
