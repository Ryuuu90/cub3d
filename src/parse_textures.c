/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:26:07 by about             #+#    #+#             */
/*   Updated: 2023/12/14 19:33:06 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub.h"

void	check_spaces(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (j == 0 && ft_isdigit(line[i]))
			j = 1;
		if (j == 1 && (line[i] == ' ' || line[i] == '\t'))
		{
			if (line[i + 1] && ft_isdigit(line[i + 1]))
				ft_error("Error: spaces somewhere!");
		}
		i++;
	}
}
char *parse_path(char *line)
{
	char	*path;
	int		len;

	path = ft_strdup(line + 3);
	len = ft_strlen(path);
	while (*path == ' ')
		path++;
	while (len > 0 && path[len - 1] == ' ')
		path[--len] = '\0';
	return (path);
}
char *remove_spaces(char *line)
{
	char	*modif;
	int		len;

	modif = ft_strdup(line);
	free(line);
	while(*modif && (*modif == ' ' || *modif == '\t'))
		modif++;
	len = ft_strlen(modif);
	if(len > 0 && (modif[len - 1] == ' ' || modif[len - 1] == '\t'))
		modif[--len] = '\0';
	return(modif);
}

void	check_missing(t_info *info)
{
	if (!info->north || !info->south || !info->west || !info->east)
		ft_error("Error: Missing texture path(s)");
	else if (!info->floor || !info->ceiling)
		ft_error("Error: Missing color");
}
void	parse_textures(t_info *info)
{    
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = info->map[info->line_index];
		if(!line)
			break ;
		line = remove_spaces(line);
		info->map[info->line_index] = line;
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		{
			info->north = parse_path(line);
			i++;	
		}
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		{
			info->south = parse_path(line);
			i++;	
		}
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		{
			info->west = parse_path(line);
			i++;	
		}
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		{
			info->east = parse_path(line);
			i++;	
		}
		else if (line[0] == 'F' && line[1] == ' ') 
			parse_colors_f(line, info , &i);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_colors_c(line, info , &i);
		info->line_index++;
    }
}
