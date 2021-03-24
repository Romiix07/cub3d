/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:11:25 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 14:02:17 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int		free_tex(t_game *g)
{
	int	i;

	i = -1;
	if (g->tex)
	{
		while (++i < 4)
		{
			if (g->tex[i].img)
			{
				mlx_destroy_image(g->mlx, g->tex[i].img);
				g->tex[i].img = NULL;
			}
			else
				break ;
		}
		free(g->tex);
		g->tex = NULL;
	}
	return (0);
}

int		free_game(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_tex(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	return (0);
}

int		free_cub(t_cub *cub)
{
	if (cub->north)
		free(cub->north);
	if (cub->east)
		free(cub->east);
	if (cub->west)
		free(cub->west);
	if (cub->south)
		free(cub->south);
	if (cub->sprite)
		free(cub->sprite);
	if (cub->map)
	{
		while ((--cub->y + 1) >= 0)
			free(cub->map[cub->y + 1]);
		free(cub->map);
	}
	return (0);
}
