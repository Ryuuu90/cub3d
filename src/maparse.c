/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:55 by about             #+#    #+#             */
/*   Updated: 2024/02/03 18:10:56 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

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
				ft_error("Error:");
			if (j <= ft_strlen(map[i]) - 1 && (!map[i - 1][j]
				|| !ft_strchr("NSEW01", map[i - 1][j])))
				ft_error("Error: thella.");
			if (!ft_strchr("NSEW01", map[i + 1][j]))
				ft_error("Error: that shouldn't be there!");
			if (!ft_strchr("NSEW01", map[i][j + 1]))
				ft_error("Error: map should be surrounded by walls");
			if (j > 0 && !ft_strchr("NSEW01", map[i][j - 1]))
				ft_error("Error: that shouldn't be there either");
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
int	find_index(char **map)
{
	int	i;
	
	i = 0;
	while(map[i])
	{
		if(map[i][0] == '1')
			break ;
		i++;
	}
	return(i);
}

void cutmap(t_info *info)
{
	int i;
	int x;
	int j;
	int len;

	i = find_index(info->map);
	x = 0;
	while (info->map[i] )
	{
		i++;
		x++;
	}
	info->map_2 = (char **)malloc(sizeof(char *) * (x + 1));
	i = find_index(info->map);
	x = 0;
	while (info->map[i])
	{
		j = 0;
		len = ft_strlen(info->map[i]);
		info->map_2[x] = (char *)malloc(sizeof(char) * (len + 1));
		while (info->map[i][j])
		{
			info->map_2[x][j] = info->map[i][j];
			j++;
		}
		info->map_2[x][j] = '\0';
		i++;
		x++;
	}
	info->map_2[x] = NULL;
}

void	parse_map(t_info *info)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	cutmap(info);
	
	while (info->map_2[i])
	{
		if (info->map_2[i][0] == '0' || info->map_2[i][0] == '\0')
			ft_error("Error: ????");
		if (i == 0)
			check_first(info->map_2[i]);
		else if (!info->map_2[i + 1])
			check_first(info->map_2[i]);
		else
			check_map(info->map_2, i , &player);
		if (info->map_2[i][ft_strlen(info->map_2[i])] == '0')
			ft_error("Error: heyd dak zero");
		i++;
	}
	if (player != 1)
		ft_error("Error: There must be only one player");
}
