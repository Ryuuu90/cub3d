/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitGame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:08 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/03 18:03:25 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"
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
	while(i < TILE * 0.1)
	{
		j = 0;
		while (j < TILE * 0.1)
		{
			my_mlx_pixel_put(img, x * (TILE * 0.1) + i , y * (TILE * 0.1) + j , color);
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
			{
				draw_square(game->img2, x, y, 0x808080);
				
			}
			if(ft_strchr("NSEW0", game->map2[y][x]))
				draw_square(game->img2 ,x , y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int linelen(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '\n')
		i++;
	return (i);
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
				player->y = y * TILE ;
				player->x = x * TILE ;
			}
			x++;
		}
		y++;
	}
}


void cutmap2(t_info *info, t_game *game)
{
	int i;
	int x;
	int j;
	int len;

	i = find_index(info->map);
	x = 0;
	while (info->map[i])
	{
		i++;
		x++;
	}
	game->map2 = (char **)malloc(sizeof(char *) * (x + 1));
	i = find_index(info->map);
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
	player->rotation_move = 0;
	player->player_angle = PI / 2;
	player->rotation_speed = 2 * (PI / 180) * 0.3;
	player->movespeed = 1 ;
}

int there_is_a_wall(t_game *game, float x, float y)
{
	if(x < 0 || y < 0 || x > WIDTH * TILE || y > HEIGHT * TILE)
		return(1);
	int wall_hit_x = (int)x / TILE;
	int wall_hit_y = (int)y / TILE;
	// if(game->map2[(int)(y / TILE)][(int)((x - 1) / TILE)] == '1')
	// 	return 1;
	if(game->map2[wall_hit_y][wall_hit_x] != '1' 
	&& game->map2[wall_hit_y][wall_hit_x] != '\n' 
	&& game->map2[wall_hit_y][wall_hit_x] != '\0'  
	&& game->map2[wall_hit_y][wall_hit_x] != '\t')
	{
		if(game->map2[(int)((y - 1) / TILE)][(int)((x + 1) / TILE)] == '1')
			return 2;
		if(game->map2[(int)((y + 1) / TILE)][(int)((x + 1) / TILE)] == '1')
			return 3;
		if(game->map2[(int)((y  - 1)/ TILE)][(int)((x - 1) / TILE)] == '1')
			return 4;
		if(game->map2[(int)((y + 1) / TILE)][(int)((x - 1) / TILE)] == '1')
			return 5;
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

void init_val_3d(t_game *game, int j, int i)
{
	if(there_is_a_wall(game, game->player->x +  cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i) == 2)
	{
		game->ray[j].wall_hit_x = (game->player->x +  cos(game->ray[j].angle) * i) + 1;
		game->ray[j].wall_hit_y = ( game->player->y + sin(game->ray[j].angle) * i) - 1;
	}
	else if(there_is_a_wall(game, game->player->x +  cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i) == 3)
	{
		game->ray[j].wall_hit_x = (game->player->x +  cos(game->ray[j].angle) * i) + 1;
		game->ray[j].wall_hit_y = ( game->player->y + sin(game->ray[j].angle) * i) + 1;
	}
	else if(there_is_a_wall(game, game->player->x +  cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i) == 4)
	{
		game->ray[j].wall_hit_x = (game->player->x +  cos(game->ray[j].angle) * i) - 1;
		game->ray[j].wall_hit_y = ( game->player->y + sin(game->ray[j].angle) * i) - 1;
	}
	else if(there_is_a_wall(game, game->player->x +  cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i) == 5)
	{
		game->ray[j].wall_hit_x = ((game->player->x - 1  )+  cos(game->ray[j].angle) * i);
		game->ray[j].wall_hit_y = ( (game->player->y + 1 )+ sin(game->ray[j].angle) * i);
	}
	else
	{
		game->ray[j].wall_hit_x = game->player->x +  cos(game->ray[j].angle) * i;
		game->ray[j].wall_hit_y =  game->player->y + sin(game->ray[j].angle) * i;
	}
    game->ray[j].distance = sqrt(pow(game->ray[j].wall_hit_x - game->player->x, 2) 
                            + pow(game->ray[j].wall_hit_y - game->player->y, 2));
    game->player->pro_wall_h = ((TILE / (game->ray[j].distance * cos(game->ray[j].angle - game->player->player_angle)))
                             * ((WIDTH / 2) / tan(FANGLE / 2)));
    game->player->top_pixel = (HEIGHT / 2) - (game->player->pro_wall_h / 2);
    if(game->player->top_pixel < 0)
        game->player->top_pixel = 0;
    game->player->bottom_pixel = (HEIGHT / 2) + (game->player->pro_wall_h / 2);
    if(game->player->bottom_pixel > HEIGHT)
        game->player->bottom_pixel = HEIGHT;
}

void render_3d_game(t_game *game, int j, int i)
{
	int l;

	l = 0;
    init_val_3d(game, j, i);
    while(l < game->player->top_pixel)
    {
        my_mlx_pixel_put(game->img2, j,l, 255);
        l++;
    }
    l = game->player->top_pixel;
    while(l < game->player->bottom_pixel)
    {
		if(game->map2[(int)((game->ray[j].wall_hit_y - 1) / TILE)][(int)((game->ray[j].wall_hit_x + 1) / TILE)] == '0'
		|| game->map2[(int)((game->ray[j].wall_hit_y - 1) / TILE)][(int)((game->ray[j].wall_hit_x + 1) / TILE)] == 'W')
			my_mlx_pixel_put(game->img2, j,l, 0xFFCCCCCC);
		if(game->map2[(int)((game->ray[j].wall_hit_y + 1) / TILE)][(int)(game->ray[j].wall_hit_x / TILE)] == '0'
		|| game->map2[(int)((game->ray[j].wall_hit_y + 1) / TILE)][(int)(game->ray[j].wall_hit_x / TILE)] == 'W')
        	my_mlx_pixel_put(game->img2, j,l, 0xFFFFFFFF);
		if(game->map2[(int)(game->ray[j].wall_hit_y / TILE)][(int)((game->ray[j].wall_hit_x + 1) / TILE)] == '0'
		|| game->map2[(int)(game->ray[j].wall_hit_y / TILE)][(int)((game->ray[j].wall_hit_x + 1) / TILE)] == 'W')
        	my_mlx_pixel_put(game->img2, j,l, 0xFFCCCCCC);
		if(game->map2[(int)((game->ray[j].wall_hit_y - 1) / TILE)][(int)(game->ray[j].wall_hit_x / TILE)] == '0'
		|| game->map2[(int)((game->ray[j].wall_hit_y - 1) / TILE)][(int)(game->ray[j].wall_hit_x / TILE)] == 'W')
        	my_mlx_pixel_put(game->img2, j,l, 0xFFFFFFFF);
		if(game->map2[(int)(game->ray[j].wall_hit_y / TILE)][(int)((game->ray[j].wall_hit_x - 1) / TILE)] == '0'
		|| game->map2[(int)(game->ray[j].wall_hit_y / TILE)][(int)((game->ray[j].wall_hit_x - 1) / TILE)] == 'W')
        	my_mlx_pixel_put(game->img2, j,l, 0xFFCCCCCC);
        l++;
    }
    l = game->player->bottom_pixel;
    while(l < HEIGHT)
    {
        my_mlx_pixel_put(game->img2, j,l, 0x2A1313);
        l++;
    }
}


void drawplayer(t_game *game)
{
    int i;
	int j;
	i = -1;
	
	if(game->flag == 1)
	{
	while (i < 1 * 0.1)
	{
		j = -1;
		while (j < 1 * 0.1)
		{
			my_mlx_pixel_put(game->img2, (game->player->x * 0.1) + i,
						(game->player->y * 0.1) + j, 0xFF000);
			j++;
		}
		i++;
	}
	}
}

void raycasting(t_game *game)
{
	int j;
	float i;
	j = 0;
	game->ray[j].angle = normalize_angle(game->player->player_angle - (FANGLE / 2));
	while(j < WIDTH )
	{
		printf("cc\n");
		i = 0.0;
		while(i < 900 && !there_is_a_wall(game, game->player->x + cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i))
			i++;
		if (roundf(fmod((game->player->x + cos(game->ray[j].angle) * i), TILE)) == 0)
   	 		game->ray[j].horiz = 1;
		else if (roundf(fmod((game->player->y + sin(game->ray[j].angle) * i), TILE)) == 0)
    		game->ray[j].horiz = 0;
		render_3d_game(game, j, i);
		game->ray[j + 1].angle = FANGLE / WIDTH + game->ray[j].angle;
		j++;
	}
		
}

int key_press(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;

	if (keycode == 65307)
		exit(1);
	if(keycode == 65363)
		game->player->sidemove = 1;
	if(keycode == 65361)
		game->player->sidemove = -1;
	if (keycode == 119)
		game->player->forwardmove = 1;
	if (keycode == 115)
		game->player->forwardmove = -1;
	if (keycode == 100)
	{
		game->player->rotation_move = 1;
		game->player->horizslid = 1;
	}
	if (keycode == 97)
	{
		game->player->rotation_move = -1;
		game->player->horizslid = -1;
	}
	if(keycode == 102)
		game->flag = 1;
	if(keycode == 114)
		game->flag = 0;
	return (0);
}

int key_release(int keycode, void *param)
{
	t_game *game;

	game = (t_game *)param;

	if (keycode == 65307)
		exit(1);
	if(keycode == 65363)
		game->player->sidemove = 0;
	if(keycode == 65361)
		game->player->sidemove = 0;
	if (keycode == 119)
		game->player->forwardmove = 0;
	else if (keycode == 115)
		game->player->forwardmove = 0;
	if (keycode == 100)
		game->player->rotation_move = 0;
	else if (keycode == 97)
		game->player->rotation_move = 0;
	return (0);
}


int check_angle_PI(float angle)
{
	if(angle >= 0 && angle <= PI / 2)
		return 1;
	if(angle > PI / 2 && angle < PI)
		return 2;
	if(angle >= PI && angle <= 3 * PI / 2)
		return 3;
	if(angle > 3 * PI / 2 && angle <=  2 * PI)
		return 4;
	return 0;
}

void update(t_game *game)
{
	game->player->player_angle += game->player->rotation_move * game->player->rotation_speed;
	game->player->player_angle = normalize_angle(game->player->player_angle);
	float movestep = game->player->forwardmove * game->player->movespeed;
	float player_x = game->player->x + cos(game->player->player_angle) * movestep;
	float player_y = game->player->y + sin(game->player->player_angle) * movestep;
	float sidestep = game->player->sidemove * game->player->movespeed;
	if(!there_is_a_wall(game, player_x, player_y))
	{
		if(!there_is_a_wall(game, player_x, game->player->y))
			game->player->x = player_x;
		if(!there_is_a_wall(game, game->player->x, player_y))
			game->player->y = player_y;
	}
	else
	{
		if(!there_is_a_wall(game, game->player->x + cos(game->player->player_angle + PI / 2) * movestep * game->player->horizslid, game->player->y))
			game->player->x = game->player->x + cos(game->player->player_angle + PI / 2) * movestep * game->player->horizslid;
		if(!there_is_a_wall(game, game->player->x , game->player->y + sin(game->player->player_angle + PI / 2) * movestep * game->player->horizslid))
			game->player->y = game->player->y + sin(game->player->player_angle + PI / 2) * movestep * game->player->horizslid;
	}
	if(!there_is_a_wall(game, game->player->x + cos(game->player->player_angle + PI / 2) * sidestep,  game->player->y))
		game->player->x = game->player->x + cos(game->player->player_angle + PI / 2) * sidestep;
	if(!there_is_a_wall(game, game->player->x ,  game->player->y + sin( game->player->player_angle + PI / 2) * sidestep))
		game->player->y = game->player->y + sin( game->player->player_angle + PI / 2) * sidestep;
}

void	draw_rays(t_game *game)
{
	int j;
	int i;

	j = 0;
	while(j < WIDTH)
	{
		
		i = 0;
		while(i < 200 && !there_is_a_wall(game, game->player->x + cos(game->ray[j].angle) * i, game->player->y + sin(game->ray[j].angle) * i))
		{
			my_mlx_pixel_put(game->img, (game->player->x * 0.1) + cos(game->ray[j].angle) * (i * 0.1),
					(game->player->y * 0.1) + sin(game->ray[j].angle) * (i * 0.1), 0xFF000);
			i++;
		}
		j+=100;
	}
}

int render(void *param)
{
	t_game *game;
	game = (t_game *) param;

	game->img2->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img2->addr = mlx_get_data_addr(game->img2->img, &game->img2->bitspixel, &game->img2->linelength, &game->img2->end);
	game->img = game->img2;
	raycasting(game);
	if(game->flag == 1)
	{
		render_2map(game);
 		drawplayer(game);
		draw_rays(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img2->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img2->img);
	update(game);
	return(0);
}

void launch_game(t_info *info, t_game *game, t_player *player, t_img *img)
{
	cutmap2(info, game);
	init_player(game, player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->player = player;
	game->img2 = img;
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}