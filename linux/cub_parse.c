/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:44:48 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/22 15:23:00 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		write(2, "Error\nWrong Resolution", 22);
	else if (c == 'T')
		write(2, "Error\nWrong Texture Path", 30);
	else if (c == 'F')
		write(2, "Error\nWrong Floor Color Code", 28);
	else if (c == 'C')
		write(2, "Error\nWrong Ceiling Color Code", 31);
	else if (c == 'c')
		write(2, "Error\nWrong Line In Configuration File", 39);
	else if (c == 'M')
		write(2, "Error\nWrong Map Configuration", 29);
	else if (c == 'A')
		write(2, "Error\nCrash While Allocating Memory", 35);
	else if (c == 'P')
		write(2, "Error\nNo Player In Map", 22);
	else if (c == 'p')
		write(2, "Error\nToo Many Player In Map", 28);
	return (0);
}

int		check_line(char *line, t_cub *cub, int index)
{
	if (line[index] == '\0')
		return (1);
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == 'R')
		return (resolution_check(line, cub, index + 1));
	else if (line[index] == 'N' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 2, 'N'));
	else if (line[index] == 'S' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 2, 'S'));
	else if (line[index] == 'E' && line[index + 1] == 'A')
		return (texture_path_check(line, cub, index + 2, 'E'));
	else if (line[index] == 'W' && line[index + 1] == 'E')
		return (texture_path_check(line, cub, index + 2, 'W'));
	else if (line[index] == 'S' && line[index + 1] == ' ')
		return (texture_path_check(line, cub, index + 1, 's'));
	else if (line[index] == 'F')
		return (floor_check(line, cub, index + 1));
	else if (line[index] == 'C')
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

	cub->start = 0;
	if ((fd = check_file_format(str)) == -1)
		return (0);
	while ((cub->error = get_next_line(fd, &line)) != 0)
	{
		if (cub->error < 0)
			return (0);
		if (cub->start == 1)
		{
			if (line_check(line) == 0)
				break ;
			tmp = ft_strjoin(cub->str, line);
			free(cub->str);
			cub->str = tmp;
		}
		else if (check_line(line, cub, 0) == 0)
			return (0);
		free(line);
	}
	close(fd);
	return (ft_map(cub));
}
