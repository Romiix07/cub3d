/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:41:15 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/30 20:31:57 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_game(t_game *game)
{
	game->player.dirx = game->cub.position.dirx;
	game->player.diry = game->cub.position.diry;
	game->player.planex = game->cub.position.planex;
	game->player.planey = game->cub.position.planey;
	game->player.posx = game->cub.position.posx;
	game->player.posy = game->cub.position.posy;
	mlx_get_screen_size(game->mlx, &game->w, &game->h);
	if (game->h >= game->cub.res_y)
		game->h = game->cub.res_y;
	if (game->w >= game->cub.res_x)
		game->w = game->cub.res_x;
}

void	cub_init(t_cub *cub)
{
	cub->start = 0;
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->sprite = NULL;
	cub->error = 0;
}
