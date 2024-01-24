/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:44:09 by about             #+#    #+#             */
/*   Updated: 2023/12/27 18:41:52 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <fcntl.h>
# include <math.h> 
# include <mlx.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# define TILE 32
# define WIDTH 1500
# define HEIGHT 1500
# define MOVE_SPEED 20
# define PI 3.1415926535
# define FANGLE 60 * (PI / 180)

typedef struct s_ray {
    float angle;
    float distance;
	float wall_hit_x;
	float wall_hit_y;
	int ver_hit;
	int left_ray;
	int right_ray;
	int up_ray;
	int down_ray;
	int cont_wall_hit; 

} t_ray;

typedef struct s_player {
	float		x;
	float		y;
	double	radius;
	double	dir_x;
	double	dir_y;
	double	player_angle;
	int		sidemove;
	int		forwardmove;
	double	rotation_dir;
	int movespeed;
	double	rotation_speed;
} t_player;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bitspixel;
	int		linelength;
	int		end;
}	t_img;
typedef struct s_game {
	void		*mlx;
	void		*win;
	void		*frame;
	char		**map2;
	int 	win_height;
	int		win_width;
	t_player	*player;
	t_img *img;
	t_img *img2;
	t_ray ray[WIDTH];
	int j;
} t_game;

typedef struct s_colors {
	int	r;
	int	g;
	int b;
} t_colors;


typedef struct s_info {
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**floor;
	char		**ceiling;
	char		**map;
	int			line_index;
	t_colors	f_1;
	t_colors	c_1;
} t_info;

void	initial(t_info *info);
void	free_all(t_info *info, t_game *game);
void	double_free(char **line);
void	parse_map(t_info *info);
// parse textures
char    **readfile(char *file);
void    ft_error(char *error);
void	parse_textures(t_info *info);
char	*parse_path(char *line);
char	*remove_spaces(char *line);
int		parse_rgb(char **line, t_info *info, int flag);
void	check_spaces(char *line);
void	check_fill(char **line, int *r ,int *g, int *b);
void	cubname(char *filename);
void	parse_colors_c(char *line, t_info *info, int *i);
void	parse_colors_f(char *line, t_info *info, int *i);
void	check_missing(t_info *info);
// parse map
void	check_map(char **map, int i, int *player);
void	check_first(char *wall);
void	parse_map(t_info *info);
void	assign(char **place, char *line, int *i);
void	check_missing(t_info *info);
// game graphics
void    launch_game(t_info *info, t_game *game, t_player *player, t_img *img);
void    render_2dmap(t_game *game);
void	draw_square(t_img *img, int x, int y, int color);
void	cutmap(t_info *info, t_game *game);;
void	get_player_pos(t_game *game, t_player *player);
void	drawplayer(t_game *game);
void	update_game(t_game *game);
void	draw_rotated(t_game *game, int x, int y, double angle);

#endif