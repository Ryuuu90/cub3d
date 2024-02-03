/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:44:09 by about             #+#    #+#             */
/*   Updated: 2024/02/03 18:02:26 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <fcntl.h>
# include <math.h> 
# include <mlx.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define TILE 64
# define WIDTH 840
# define HEIGHT 430
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
	int horiz;
	int cont_wall_hit; 
} t_ray;

typedef struct s_player {
	float		x;
	float		y;
	float		xr;
	float		yr;
	float	radius;
	float	player_angle;
	int		sidemove;
	int		rotation_move;
	int		forwardmove;
	float	rotation_dir;
	float movespeed;
	float	rotation_speed;
	long pro_wall_h;
	long top_pixel;
	long	bottom_pixel;
	int horizslid;
	
} t_player;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bitspixel;
	int		linelength;
	int		end;
}	t_img;
typedef struct s_game {
	int			flag;
	void		*mlx;
	void		*win;
	void		*frame;
	char		**map2;
	int 	win_height;
	int		win_width;
	t_player	*player;
	t_img *img;
	t_img *img2;
	int j;
	t_ray ray[WIDTH];
	int i;
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
	char		**map_2;
	int			found_no;
	int			found_so;
	int			found_we;
	int			found_ea;
	int			found_f;
	int			found_c;
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
void	cubname(char *filename, char *name, char *error);
void	parse_colors_c(char *line, t_info *info, int *i, int *flag);
void	parse_colors_f(char *line, t_info *info, int *i, int *flag);
void	check_missing(t_info *info);
// parse map
int		find_index(char **map);
void	cutmap(t_info *info);
void	check_map(char **map, int i, int *player);
void	check_first(char *wall);
void	parse_map(t_info *info);
void	assign(char **place, char *line, int *i);
void	check_missing(t_info *info);
char	*parse_path(char *line);
void	assignthis(char **texture, char *line, int *i, int *flag);
// game graphics
void    launch_game(t_info *info, t_game *game, t_player *player, t_img *img);
void    render_2dmap(t_game *game);
void	draw_square(t_img *img, int x, int y, int color);
void	cutmap2(t_info *info, t_game *game);;
void	get_player_pos(t_game *game, t_player *player);
void	drawplayer(t_game *game);
void	update_game(t_game *game);
void	draw_rotated(t_game *game, int x, int y, double angle);

#endif