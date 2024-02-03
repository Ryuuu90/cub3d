/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:39:34 by about             #+#    #+#             */
/*   Updated: 2024/01/29 23:00:55 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_info		info;
	t_game		game;
	t_player	player;
	t_img		img;
	
	if (ac != 2)
	{
		write(2, "Error\nWrong number of arguments\n", 31);
		return 1;
	}
	info.map = readfile(av[1]);
	if (!info.map)
		ft_error("Empty file!");
	(initial(&info), parse_textures(&info), check_missing(&info) );
	parse_map(&info);
	launch_game(&info, &game, &player, &img);
	free_all(&info, &game);
	return (0);
}
