/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:43:02 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:43:39 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

int		get_tex(t_game *g, t_cub *c)
{
	int	i;

	if (!(g->tex = malloc(sizeof(t_img) * 4)))
		return (0);
	if (!(g->tex[0].img = mlx_xpm_file_to_image(g->mlx, c->north,
												&g->tex[0].width,
												&g->tex[0].height)))
		return (0);
	if (!(g->tex[1].img = mlx_xpm_file_to_image(g->mlx, c->south,
												&g->tex[1].width,
												&g->tex[1].height)))
		return (0);
	if (!(g->tex[2].img = mlx_xpm_file_to_image(g->mlx, c->west,
												&g->tex[2].width,
												&g->tex[2].height)))
		return (0);
	if (!(g->tex[3].img = mlx_xpm_file_to_image(g->mlx, c->east,
												&g->tex[3].width,
												&g->tex[3].height)))
		return (0);
	i = -1;
	while (++i < 4)
		g->tex[i].addr = mlx_get_data_addr(g->tex[i].img, &g->tex[i].bpp,
									&g->tex[i].line_length,	&g->tex[i].endian);
	return (1);
}

int		init_game(t_game *game, t_cub *cub)
{
	if (!(game->mlx = mlx_init()))
		return (free_game(game) + free_cub(cub));
	if (!(game->win = mlx_new_window(game->mlx, cub->res_x, cub->res_y, 
									 "T'es finito, tu n'es qu'une fraude")))
		return (free_game(game) + free_cub(cub));
	if (!(game->img.img = mlx_new_image(game->mlx, cub->res_x, cub->res_y)))
		return (free_game(game) + free_cub(cub));
	if (!(get_tex(game, cub)))
		return (free_game(game) + free_cub(cub));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
									  &game->img.line_length,
									  &game->img.endian);
	game->h = cub->res_y;
	game->w = cub->res_x;
	game->cub = *cub;
	for (int i = 0; i <= game->cub.y; ++i)
		for (int j = 0; j <= game->cub.x; ++j)
			if (game->cub.map[i][j] == 'N' || game->cub.map[i][j] == 'S' ||
				game->cub.map[i][j] == 'E' || game->cub.map[i][j] == 'W')
				game->cub.map[i][j] = '0';
	game->player.posx = 4.0;
	game->player.posy = 4.0;
	game->player.dirx = 0.0;
	game->player.diry = 1.0;
	game->player.planex = 0.60;
	game->player.planey = 0.00;
	game->player.movespeed = 0.12;
	game->player.rotspeed = 0.05;
	game->player.move_w = 0;
	game->player.move_a = 0;
	game->player.move_s = 0;
	game->player.move_d = 0;
	game->player.rot_r = 0;
	game->player.rot_l = 0;
	return (1);
}
