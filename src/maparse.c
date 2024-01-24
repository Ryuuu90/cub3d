/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:55 by about             #+#    #+#             */
/*   Updated: 2023/12/14 19:24:20 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub.h"

void	check_map(char **map, int i, int *player)
{
	size_t	j;

	j = 0;
	while (map[i][j])
	{
		if(ft_strchr("NSWE", map[i][j]))
			(*player)++;
		if(ft_strchr("NSEW0", map[i][j]))
		{
			if (map[i + 1] && j > ft_strlen(map[i + 1]))
				ft_error("Error: no.");
			if (j <= ft_strlen(map[i]) - 1 && (!map[i - 1][j]
				|| !ft_strchr("NSEW01", map[i - 1][j])))
				ft_error("Error: thella.");
			if (!ft_strchr("NSEW01", map[i + 1][j]))
				ft_error("Error: that shouldn't be there!");
			if (!ft_strchr("NSEW01", map[i][j + 1]))
				ft_error("Error: map should be surrounded be walls");
			if (j > 0 && !ft_strchr("NSEW01", map[i][j - 1]))
				ft_error("Error: ");
		}
		j++;
	}
}

void	check_first(char *wall)
{
	int	i;

	i = 0;
	while (wall[i])
	{
		if (wall[i] == '\n')
			break;
		if (wall[i] != '1' && wall[i] != ' ' && wall[i] != '\t')
			ft_error("Error: map should be closed by walls");
		i++;
	}
}
void	parse_map(t_info *info)
{
	int	i;
	int	player;

	i = info->line_index + 1;
	player = 0;
	while (info->map[i])
	{
		if (info->map[i][0] == '0' || info->map[i][0] == '\0')
			ft_error("Error: ????");
		if (i == info->line_index + 1)
			check_first(info->map[i]);
		else if (!info->map[i + 1])
			check_first(info->map[i]);
		else
			check_map(info->map, i , &player);
		if (info->map[i][ft_strlen(info->map[i])] == '0')
			ft_error("Error: heyd dak zero");
		i++;
	}
	if (player != 1)
		ft_error("Error: There must be only one player");
}
