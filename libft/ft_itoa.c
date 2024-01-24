/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:31:51 by about             #+#    #+#             */
/*   Updated: 2022/11/01 14:59:11 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	len(int j)
{
	int	i;

	i = 0;
	if (j == 0)
		i++;
	if (j < 0)
		i++;
	while (j)
	{
		j = j / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = len(n);
	p = malloc(sizeof(char) * i + 1);
	if (!p)
		return (0);
	p[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		p[0] = '-';
	}
	while (n)
	{
		p[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (p);
}
