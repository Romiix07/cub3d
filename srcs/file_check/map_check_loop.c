/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:26:53 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 02:06:01 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check_loop(t_cub *cub, int i, int j)
{
	if (cub->map[j][i] != '1')
	{
		if (cub->map[j][i] == 'N' || cub->map[j][i] == 'W' ||
			cub->map[j][i] == 'S' || cub->map[j][i] == 'E')
			pos_edit(cub, j, i);
		if ((j == 0 || j == cub->y) && (border(cub->map, i, j, cub->x))
			== 0)
			return (error_code('M') + free_cub(cub) + ft_memdel(&cub->str, 0));
		if (j > 0 && j < cub->y && (core(cub->map, i, j, cub->x)) == 0)
			return (error_code('M') + free_cub(cub) + ft_memdel(&cub->str, 0));
	}
	return (1);
}
