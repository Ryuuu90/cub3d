/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:23:29 by about             #+#    #+#             */
/*   Updated: 2023/12/27 22:09:25 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if(y >= HEIGHT || x >= WIDTH || y <= 0 || x <= 0)
		return;
	dst = data->addr + (y * data->linelength + x * (data->bitspixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_img *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while(i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(img, x * 10 + i , y * 10 + j , color);
			j++;
		}
		i++;
	}
}
void render_2map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while(game->map2[y])
	{
		x = 0;
		while(game->map2[y][x])
		{
			if(game->map2[y][x] == '1')
				draw_square(game->img, x, y, 0x808080);
			else if(ft_strchr("NSEW0", game->map2[y][x]))
				draw_square(game->img, x , y, 0xFFFFFF);
			x++;
		}
		// if (game->map2[y][x] == '\n')
			y++;
	}
}
void get_map_h_w(t_game *game)
{
	int y;
	// int x;

	y = 0;
	while(game->map2[y])
	{
		if(game->map2[y + 1] && ft_strlen(game->map2[y + 1]) > ft_strlen(game->map2[y]))
			game->win_width = ft_strlen(game->map2[y + 1]) * 10;
		else 
			game->win_width = ft_strlen(game->map2[y]) * 10;
		y++;
	}
	game->win_height = y * 10;
	// printf("w == %d\nh == %d\n", game->win_width, game->win_height);
}
void get_player_pos(t_game *game, t_player *player)
{
	int y;
	int x;

	y = 0;
	while (game->map2[y])
	{
		x = 0;
		while (game->map2[y][x] && game->map2[y][x] != '\n')
		{
			if (ft_strchr("NSEW", game->map2[y][x]))
			{
				player->y = y * TILE;
				player->x = x * TILE;
			}
			x++;
		}
		y++;
	}
}


void cutmap(t_info *info, t_game *game)
{
	int i;
	int x;
	int j;
	int len;

	i = info->line_index + 1;
	x = 0;
	while (info->map[i])
	{
		i++;
		x++;
	}
	game->map2 = (char **)malloc(sizeof(char *) * (x + 1));
	i = info->line_index + 1;
	x = 0;
	while (info->map[i])
	{
		j = 0;
		len = ft_strlen(info->map[i]);
		game->map2[x] = (char *)malloc(sizeof(char) * (len + 1));
		while (info->map[i][j])
		{
			game->map2[x][j] = info->map[i][j];
			j++;
		}
		game->map2[x][j] = '\0';
		i++;
		x++;
	}
	game->map2[x] = NULL;
}

void init_player(t_game *game, t_player *player)
{
	get_player_pos(game, player);
	player->radius = 3;
	player->forwardmove = 0;
	player->sidemove = 0;
	player->player_angle = PI / 2;
	player->rotation_speed = 2 * (PI / 180);
	player->movespeed = 2;
}
int there_is_a_wall(t_game *game, float x, float y)
{
	if(x < 0 || y < 0 || x > 5120 || y > 3520)
		return(1);
	int wall_hit_x = floor(x / TILE);
	int wall_hit_y = floor(y / TILE);

	if(game->map2[wall_hit_y][wall_hit_x] != '1' && game->map2[wall_hit_y][wall_hit_x] != '\n' && game->map2[wall_hit_y][wall_hit_x] != '\0' && game->map2[wall_hit_y][wall_hit_x] != ' ' && game->map2[wall_hit_y][wall_hit_x] != '\t')
	{
		return(0);
	}
	return(1);
}
float normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, PI * 2);
	if(ray_angle < 0)
	{
		ray_angle = PI * 2 + ray_angle; 
	}
	return(ray_angle);
}


void drawplayer(t_game *game)
{
	int i;
	int j;
	i = -2;
	
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			my_mlx_pixel_put(game->img, (game->player->x + i) * 0.2, (game->player->y + j) * 0.2, 0xFF000);
			j++;
		}
		i++;
	}
	j = 0;
	game->ray[j].wall_hit_x = 0;
	game->ray[j].wall_hit_y = 0;
	game->ray[j].angle = normalize_angle( game->player->player_angle - (FANGLE / 2));

	int pro_wall_h = 0;
	int bottom_pixel = 0;
	int top_pixel = 0;
	int l = 0;
	while(j < WIDTH)
	{
		i = 0;
		while(!there_is_a_wall(game, game->player->x +  cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i) && i < 900)
		{
			// else
			// {
			// 	game->ray[j].wall_hit_x = -1;
			// 	game->ray[j].wall_hit_y = -1;
			if(i < 200)
			{
				my_mlx_pixel_put(game->img, (game->player->x + cos(game->ray[j].angle) * i) * 0.2,
					(game->player->y + sin(game->ray[j].angle) * i) * 0.2, 0xFF000);
			}
			// }
			i++;
		}
		game->ray[j].wall_hit_x = game->player->x +  cos(game->ray[j].angle) * i;
		game->ray[j].wall_hit_y =  game->player->y + sin(game->ray[j].angle) * i;
		game->ray[j].distance = sqrt(pow(game->ray[j].wall_hit_x - game->player->x, 2) + pow(game->ray[j].wall_hit_y - game->player->y, 2));
		pro_wall_h = (int)((TILE / (game->ray[j].distance * cos(game->ray[j].angle - game->player->player_angle))) * ((WIDTH / 2) / tan(FANGLE / 2)));
		top_pixel = (HEIGHT / 2) - (pro_wall_h / 2);
		if(top_pixel < 0)
			top_pixel = 0;
		bottom_pixel = (HEIGHT / 2) + (pro_wall_h / 2);
			// printf("%d\n", top_pixel, bottom_pixel);
		if(bottom_pixel > HEIGHT)
			bottom_pixel = HEIGHT;
		l = 0;
		while(l < top_pixel)
		{
			my_mlx_pixel_put(game->img2,j,
					l, 255);
			l++;
		}
		l = top_pixel;
		while(l < bottom_pixel)
		{
			my_mlx_pixel_put(game->img2,j,
					l, 0xFF000);
			l++;
		}
		l = bottom_pixel;
		while(l < HEIGHT)
		{
			my_mlx_pixel_put(game->img2,j,
					l, 0x2A1313);
			l++;
		}
		game->ray[j + 1].angle = FANGLE / WIDTH + game->ray[j].angle;
		j++;
	}
		
}
int key_press(int keycode, void *param)
{
	t_player *player;

	player = (t_player *)param;

	if (keycode == 53)
		exit(1);
	if (keycode == 13 || keycode == 126)
		player->forwardmove = 1;
	else if (keycode == 1 || keycode == 125)
		player->forwardmove = -1;
	if (keycode == 2 || keycode == 124)
		player->sidemove = 1;
	else if (keycode == 0 || keycode == 123)
		player->sidemove = -1;
	// update_game(game);
	return (0);
}
int key_release(int keycode, void *param)
{
	t_player *player;

	player = (t_player *)param;

	if (keycode == 53)
		exit(1);
	if (keycode == 13 || keycode == 126)
		player->forwardmove = 0;
	else if (keycode == 1 || keycode == 125)
		player->forwardmove = 0;
	if (keycode == 2 || keycode == 124)
		player->sidemove = 0;
	else if (keycode == 0 || keycode == 123)
		player->sidemove = 0;
	// update_game(game);
	return (0);
}

void update(t_game *game)
{
	game->player->player_angle += game->player->sidemove * game->player->rotation_speed;
	float movestep = game->player->forwardmove * game->player->movespeed;
	float player_x = game->player->x + cos(game->player->player_angle) * movestep;
	float player_y = game->player->y + sin(game->player->player_angle) * movestep;
	if(!there_is_a_wall(game, player_x, player_y))
	{
		game->player->x = player_x;
		game->player->y = player_y;
	}
	// cast_rays
}

void	generete_3d(t_game *game)
{
	int i = 0;
	int j = 0;
	int pro_wall_h;
	int top_pixel;
	int bottom_pixel;
	while(i < WIDTH)
	{
		pro_wall_h = ((TILE / (floor(game->ray[i].distance )) * ((WIDTH / 2) / tan(FANGLE / 2))));
		top_pixel = (HEIGHT / 2) - (pro_wall_h / 2);
		if(top_pixel < 0)
			top_pixel = 0;
		bottom_pixel = (HEIGHT / 2) + (pro_wall_h / 2);
		if(bottom_pixel > HEIGHT)
			bottom_pixel = HEIGHT;
		j = 0;
		while(j < top_pixel)
		{
			my_mlx_pixel_put(game->img2,i,
					j, 0x4d1c31);
			j++;
		}
		j = top_pixel;
		while(j < bottom_pixel)
		{
			my_mlx_pixel_put(game->img2,i,
					j, 0xFF000 - game->ray[i].distance);
			j++;
		}
		j = bottom_pixel;
		while(j < HEIGHT)
		{
			my_mlx_pixel_put(game->img2,i,
					j, 0x2A1313);
			j++;
		}
		i++;
	}
}

int render(void *param)
{
	t_game *game;
	game = (t_game *) param;
	t_img img;
	get_map_h_w(game);
	game->img2 = &img;
	game->img->img = mlx_new_image(game->mlx, game->win_width , game->win_height );
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bitspixel, &game->img->linelength, &game->img->end);
	game->img2->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img2->addr = mlx_get_data_addr(game->img2->img, &game->img2->bitspixel, &game->img2->linelength, &game->img2->end);
	// render_2map(game);
 	 drawplayer(game);
	// generete_3d(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game->player);
	mlx_hook(game->win, 3, 1L << 1, key_release, game->player);
	update(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img2->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img2->img);
	mlx_destroy_image(game->mlx, game->img->img);
	return(0);
}

void launch_game(t_info *info, t_game *game, t_player *player, t_img *img)
{
	cutmap(info, game);
	init_player(game, player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->player = player;
	game->img = img;
	game->img = malloc(sizeof(t_img));
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}