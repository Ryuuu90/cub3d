/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:09:07 by about             #+#    #+#             */
/*   Updated: 2022/11/01 15:06:39 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	p;
	size_t			i;

	p = (unsigned char)c;
	i = 0;
	while (s[i] != '\0' && s[i] != p)
	{
		i++;
	}
	if (s[i] == p)
	{
		return ((char *)s + i);
	}
	return (NULL);
}
