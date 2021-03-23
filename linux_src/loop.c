/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:43:28 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/23 16:02:28 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3d.h"
#include "cub3d_defines.h"
#include "cub.h"

void	fill_buffer(t_game *game, t_camera *cam, int x, t_img img)
{
	int	y;
	int color;

	y = -1;
	while (++y < cam->drawstart)
		my_mlx_pixel_put(&game->img, x, y, game->cub.ceiling_color);
	cam->step = 1.0 * img.height / cam->lineheight;
	cam->texpos = (cam->drawstart - game->h / 2 + cam->lineheight / 2) *
		cam->step;
	while (y < cam->drawend)
	{
		cam->texy = (int)cam->texpos & (img.height - 1);
		cam->texpos += cam->step;
		my_mlx_pixel_put(&game->img, x, y, *(int *)(img.addr +
													(cam->texy *
													 img.line_length +
													 cam->texx *
													 (img.bpp /
													  8))));
		++y;
	}
	while ((++y - 1) < game->h)
		my_mlx_pixel_put(&game->img, x, y - 1,
						 game->cub.floor_color);
}

void	get_wallx_texx(t_game *game, t_player *player, t_camera *cam, t_img img)
{
	if (cam->side == 0)
		cam->wallx = player->posy + cam->perpwalldist * cam->raydiry;
	else
		cam->wallx = player->posx + cam->perpwalldist * cam->raydirx;
	cam->wallx -= cam->wallx < 0 ? (int)cam->wallx - 1 : (int)cam->wallx;
	cam->texx = (int)(cam->wallx * (double)img.width);
	if (cam->side == 0 && cam->raydirx > 0)
		cam->texx = img.width - cam->texx - 1;
	if (cam->side == 1 && cam->raydiry < 0)
		cam->texx = img.width - cam->texx - 1;
}

int		get_color(t_game *game)
{
	int	index;

	if (game->camera.mapy > game->player.posy && game->camera.side == 1)
		index = EAST;
	else if (game->camera.mapx > game->player.posx && game->camera.side == 0)
		index = SOUTH;
	else if (game->camera.mapy <= game->player.posy && game->camera.side == 1)
		index = WEST;
	else
		index = NORTH;
	return (index);
}

void	get_perp_drawstartend(t_game *game, t_player *player, t_camera *camera)
{
	if (camera->side == 0)
		camera->perpwalldist = (camera->mapx - player->posx
								+ (1 - camera->stepx) /
								2) / camera->raydirx;
	else
		camera->perpwalldist = (camera->mapy - player->posy
								+ (1 - camera->stepy) /
								2) / camera->raydiry;

	camera->lineheight = (int)(game->h / camera->perpwalldist);
	camera->drawstart = -camera->lineheight / 2 + game->h / 2;
	if (camera->drawstart < 0)
		camera->drawstart = 0;
	camera->drawend = camera->lineheight / 2 + game->h / 2;
	if (camera->drawend >= game->h)
		camera->drawend = game->h - 1;
}

void	perform_dda(t_player *player, t_camera *camera, t_cub cub)
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
		if (cub.map[camera->mapx][camera->mapy] != '0')
			camera->hit = 1;
	}
}

void	get_step_sidedist(t_player *player, t_camera *camera)
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

void	get_base_values(t_game *game, t_player *player, t_camera *camera, int x)
{
	camera->camerax = 2 * x / (double)game->w - 1;
	camera->raydirx = player->dirx + player->planex * camera->camerax;
	camera->raydiry = player->diry + player->planey * camera->camerax;
	camera->mapx = (int)player->posx;
	camera->mapy = (int)player->posy;
	camera->deltadistx = fabs(1 / camera->raydirx);
	camera->deltadisty = fabs(1 / camera->raydiry);
}

int raycast(t_game *game, t_cub cub)
{
	int	x;
	int	index;

	x = 0;
	while (x < game->w)
	{
		get_base_values(game, &game->player, &game->camera, x);
		get_step_sidedist(&game->player, &game->camera);
		perform_dda(&game->player, &game->camera, cub);
		get_perp_drawstartend(game, &game->player, &game->camera);
		index = get_color(game);
/*		//get color
		if (game->camera.mapy > game->player.posy && game->camera.side == 1)      //EAST
			index = RGB_GREEN;
        else if (game->camera.mapx > game->player.posx && game->camera.side == 0) //SOUTH
			index = RGB_RED;
        else if (game->camera.mapy <= game->player.posy && game->camera.side == 1) //WEST
			index = RGB_BLUE;
        else                                                                      //NORTH
			index = RGB_WHITE;
*/
		get_wallx_texx(game, &game->player, &game->camera, game->tex[index]);
		fill_buffer(game, &game->camera, x, game->tex[index]);
		++x;
	}
	return (1);
}
