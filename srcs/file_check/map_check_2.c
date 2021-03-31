/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:49:41 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 02:05:42 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		pos_edit(t_cub *cub, int j, int i)
{
	cub->position.dirx = 0;
	cub->position.diry = 0;
	cub->position.planex = 0;
	cub->position.planey = 0;
	cub->position.posx = j + 0.5;
	cub->position.posy = i + 0.5;
	cub->is_player += 1;
	if (cub->map[j][i] == 'N')
		cub->position.dirx = -1.0;
	if (cub->map[j][i] == 'S')
		cub->position.dirx = 1.0;
	if (cub->map[j][i] == 'E')
		cub->position.diry = 1.0;
	if (cub->map[j][i] == 'W')
		cub->position.diry = -1.0;
	if (cub->position.dirx == -1.0)
		cub->position.planey = 0.60;
	else if (cub->position.dirx == 1.0)
		cub->position.planey = -0.60;
	if (cub->position.diry == 1.0)
		cub->position.planex = 0.60;
	else if (cub->position.diry == -1.0)
		cub->position.planex = -0.60;
	cub->map[j][i] = '0';
	return (1);
}

int		map_create(char *lines, int ***map, int *y, int *x)
{
	int index;
	int	count;

	index = -1;
	*y = 0;
	while (lines[++index])
	{
		if (lines[index] == '\n')
			*y += 1;
	}
	if (!(*map = malloc(sizeof(int *) * *y)))
		return (error_code('A'));
	index = -1;
	count = 0;
	*x = 0;
	while (lines[++index])
	{
		if (*x < count && lines[index] == '\n')
			*x = count;
		count = (lines[index] == '\n' ? 0 : count + 1);
	}
	while (count < *y)
		if (!(map[0][count++] = malloc(sizeof(int) * *x)))
			return (error_code('A'));
	return (1);
}

int		border_map_check_2(int **map, int i, int j, int x)
{
	if (i == x)
	{
		if (j == 0)
			if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
		if (j > 0)
			if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
	}
	if (i > 0 && i < x)
	{
		if (j == 0)
			if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
				(map[j][i + 1] != 32 && map[j][i + 1] != '1') ||
				(map[j][i - 1] != 32 && map[j][i + 1] != '1'))
				return (0);
		if (j > 0)
			if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
				(map[j][i + 1] != 32 && map[j][i + 1] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
	}
	return (1);
}

int		core_map_check_2(int **map, int i, int j, int t)
{
	if (i == 0)
	{
		if ((map[j + 1][i] != t && map[j + 1][i] != '1') ||
			(map[j][i + 1] != t && map[j][i + 1] != '1') ||
			(map[j - 1][i] != t && map[j - 1][i] != '1'))
			return (0);
	}
	return (1);
}

int		core_set(int **map, int j, int i, int t)
{
	if (map[j][i] != t && map[j][i] != '1' && map[j][i] != 'N'
			&& map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W' &&
		map[j][i] != '2')
		return (0);
	return (1);
}
