/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:28:19 by about             #+#    #+#             */
/*   Updated: 2023/12/20 21:27:28 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}
void	free_all(t_info *info, t_game *game)
{
	free(info->north);
	free(info->south);
	free(info->east);
	free(info->west);
	double_free(info->floor);
	double_free(info->ceiling);
	double_free(game->map2);
}
void	double_free(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}
void	initial(t_info *info)
{
	info->west = NULL;
	info->south = NULL;
	info->north = NULL;
	info->east = NULL;
	info->ceiling = 0;
	info->floor = 0;
	info->line_index = 0;
	info->f_1.r = 0;
	info->f_1.g = 0;
	info->f_1.b = 0;
	info->c_1.r = 0;
	info->c_1.g = 0;
	info->c_1.b = 0;
}
void	assign(char **place, char *line, int *i)
{
	*place = parse_path(line);
	(*i)++;
}
