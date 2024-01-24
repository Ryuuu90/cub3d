/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:45:44 by about             #+#    #+#             */
/*   Updated: 2023/11/27 15:37:31 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size && count > 2147483647 / size)
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (0);
	ft_bzero (str, (count * size));
	return (str);
}
