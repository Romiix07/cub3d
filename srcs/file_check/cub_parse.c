/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:49:25 by rmouduri          #+#    #+#             */
/*   Updated: 2021/04/04 17:15:06 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "cub3d.h"

int		check_file_format(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '.')
		++i;
	if (!ft_strcmp(&str[i], ".cub"))
		if ((i = open(str, O_RDONLY)) > -1)
			return (i);
	write(2, "Error\n", 6);
	write(2, "Wrong Format for ", 18);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (-1);
}

int		error_code(char c)
{
	if (c == 'R')
		write(2, "Error\nWrong Resolution\n", 23);
	else if (c == 'T')
		write(2, "Error\nWrong Texture Path\n", 25);
	else if (c == 'F')
		write(2, "Error\nWrong Floor Color Code\n", 29);
	else if (c == 'C')
		write(2, "Error\nWrong Ceiling Color Code\n", 31);
	else if (c == 'c')
		write(2, "Error\nWrong Line In Configuration File\n", 39);
	else if (c == 'M')
		write(2, "Error\nWrong Map Configuration\n", 30);
	else if (c == 'A')
		write(2, "Error\nCrash While Allocating Memory\n", 36);
	else if (c == 'P')
		write(2, "Error\nNo Player In Map\n", 23);
	else if (c == 'p')
		write(2, "Error\nToo Many Player In Map\n", 29);
	return (0);
}

int		check_line(char *line, t_cub *cub, int index)
{
	if (line[index] == '\0')
		return (1);
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == 'R' && cub->res_x == -1 && cub->res_y == -1)
		return (resolution_check(line, cub, index + 1));
	else if (!ft_strncmp(&line[index], "NO", 2) && !cub->north)
		return (texture_path_check(line, cub, index + 2, 'N'));
	else if (!ft_strncmp(&line[index], "SO", 2) && !cub->south)
		return (texture_path_check(line, cub, index + 2, 'S'));
	else if (!ft_strncmp(&line[index], "EA", 2) && !cub->east)
		return (texture_path_check(line, cub, index + 2, 'E'));
	else if (!ft_strncmp(&line[index], "WE", 2) && !cub->west)
		return (texture_path_check(line, cub, index + 2, 'W'));
	else if (line[index] == 'S' && !cub->sprite)
		return (texture_path_check(line, cub, index + 1, 's'));
	else if (line[index] == 'F' && cub->floor_color == -1)
		return (floor_check(line, cub, index + 1));
	else if (line[index] == 'C' && cub->ceiling_color == -1)
		return (ceiling_check(line, cub, index + 1));
	else if (line[index] == '1')
		return (map_verif(line, cub));
	return (error_code('c'));
}

int		ft_map(t_cub *cub)
{
	if (map_create(cub->str, &cub->map, &cub->y, &cub->x) == 0)
		return (0);
	if (map_edit(cub) == 0)
		return (0);
	free(cub->str);
	return (1);
}

int		cub_parse(char *str, t_cub *cub)
{
	char	*tmp;
	int		fd;
	char	*line;

	cub_init(cub);
	if ((fd = check_file_format(str)) == -1)
		return (0);
	while ((cub->ret = get_next_line(fd, &line)) >= 0)
	{
		if (cub->start == 1 && (ft_strlen(line) || cub->ret))
		{
			tmp = ft_strjoin(cub->str, line);
			free(cub->str);
			cub->str = tmp;
		}
		else if (check_line(line, cub, 0) == 0)
			cub->error = -1;
		ft_memdel(&line, 0);
		if (cub->ret == 0)
			break ;
	}
	last_check(cub) == 0 ? cub->error = -1 : 0;
	cub->ret = cub->error;
	return (cub->ret == -1 ? ft_memdel(&line, fd) + free_parse(cub) :
			ft_map(cub) + ft_memdel(&line, fd));
}
