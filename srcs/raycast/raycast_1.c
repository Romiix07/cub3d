/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:43:28 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/25 14:57:47 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

static void	perform_dda(t_camera *camera, t_cub cub)
{
	camera->hit = 0;
	while (camera->hit == 0)
	{
		if (camera->sidedistx < camera->sidedisty)
		{
			camera->sidedistx += camera->deltadistx;
			camera->mapx += camera->stepx;
			camera->side = 0;
		}
		else
		{
			camera->sidedisty += camera->deltadisty;
			camera->mapy += camera->stepy;
			camera->side = 1;
		}
		if (cub.map[camera->mapx][camera->mapy] == '1')
			camera->hit = 1;
	}
}

static void	get_step_sidedist(t_player *player, t_camera *camera)
{
	if (camera->raydirx < 0)
	{
		camera->stepx = -1;
		camera->sidedistx = (player->posx - camera->mapx) *
			camera->deltadistx;
	}
	else
	{
		camera->stepx = 1;
		camera->sidedistx = (camera->mapx + 1.0 - player->posx) *
			camera->deltadistx;
	}
	if (camera->raydiry < 0)
	{
		camera->stepy = -1;
		camera->sidedisty = (player->posy - camera->mapy) *
			camera->deltadisty;
	}
	else
	{
		camera->stepy = 1;
		camera->sidedisty = (camera->mapy + 1.0 - player->posy) *
			camera->deltadisty;
	}
}

static void	get_base_values(t_game *game, t_player *player,
							t_camera *camera, int x)
{
	camera->camerax = 2 * x / (double)game->w - 1;
	camera->raydirx = player->dirx + player->planex * camera->camerax;
	camera->raydiry = player->diry + player->planey * camera->camerax;
	camera->mapx = (int)player->posx;
	camera->mapy = (int)player->posy;
	camera->deltadistx = fabs(1 / camera->raydirx);
	camera->deltadisty = fabs(1 / camera->raydiry);
}

int			raycast(t_game *game, t_cub cub)
{
	int		x;
	int		index;
	double	zbuffer[game->w];

	x = 0;
	while (x < game->w)
	{
		get_base_values(game, &game->player, &game->camera, x);
		get_step_sidedist(&game->player, &game->camera);
		perform_dda(&game->camera, cub);
		get_perp_drawstartend(game, &game->player, &game->camera);
		zbuffer[x] = game->camera.perpwalldist;
		index = select_texture(game);
		get_wallx_texx(&game->player, &game->camera, game->tex[index]);
		fill_line(game, &game->camera, x, game->tex[index]);
		++x;
	}
	draw_sprites(game, (double *)zbuffer);
	return (1);
}
