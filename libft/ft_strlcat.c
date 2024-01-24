/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:21:34 by about             #+#    #+#             */
/*   Updated: 2022/11/01 15:10:21 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendst;

	i = 0;
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (dstsize < lendst)
		return (lensrc + dstsize);
	while (src[i] != '\0' && i + 1 < dstsize - lendst)
	{
		dst[lendst + i] = src[i];
		i++;
	}
		dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
