/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:02:45 by about             #+#    #+#             */
/*   Updated: 2024/02/03 17:46:35 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	cubname(char *filename, char *name, char *error)
{
	int len = ft_strlen(filename);

	if (len < 4 || strcmp(filename + len - 4, name) != 0)
		ft_error(error);
}
char	**readfile(char *file)
{
	int fd;
	int i;
	int j;
	char **mapped;
	char *tmp;

	cubname(file, ".cub", "Error: The filename must be in .cub format");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Could not open file.");
	i = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break;
		free(tmp);
		i++;
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Could not open file.");
	mapped = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j <= i)
		mapped[j++] = get_next_line(fd);
	close(fd);
	return (mapped);
}
