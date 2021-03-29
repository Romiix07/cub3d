/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:05:59 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/29 15:23:50 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub3d_defines.h"

static void	write_sprite(t_game *g, t_spriteval *val, double *zbuf, int i)
{
	int				stripe;
	int				d;
	unsigned int	color;
	int				y;

	stripe = val->drawstartx - 1;
	while (++stripe < val->drawendx)
	{
		g->camera.texx = (int)(256 * (stripe - (-g->sprite[i].width / 2 +
							val->spritescreenx)) * g->sprite_tex.width /
							g->sprite[i].width) / 256;
		y = val->drawstarty - 1;
		if (val->transformy > 0 && stripe > 0 && val->transformy < zbuf[stripe])
			while (++y < val->drawendy)
			{
				d = (y) * 256 - g->h * 128 + g->sprite[i].height * 128;
				g->camera.texy = ((d * g->sprite_tex.height) /
								g->sprite[i].height) / 256;
				color = *(unsigned int *)(g->sprite_tex.addr +
							g->camera.texy * g->sprite_tex.line_length +
							g->camera.texx * (g->sprite_tex.bpp / 8));
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put_bmp(g->fd, color);
			}
	}
}

static void	get_sprite_values(t_game *game, t_spriteval *val, int i)
{
	val->spritex = game->sprite[i].x - game->player.posx;
	val->spritey = game->sprite[i].y - game->player.posy;
	val->invdet = 1.0 / (game->player.planex * game->player.diry -
						game->player.dirx * game->player.planey);
	val->transformx = val->invdet * (game->player.diry * val->spritex
									- game->player.dirx * val->spritey);
	val->transformy = val->invdet * (-game->player.planey * val->spritex +
									game->player.planex * val->spritey);
	val->spritescreenx = (int)((game->w / 2) * (1 + val->transformx /
												val->transformy));
	game->sprite[i].height = abs((int)(game->h / (val->transformy)));
	val->drawstarty = -game->sprite[i].height / 2 + game->h / 2;
	if (val->drawstarty < 0)
		val->drawstarty = 0;
	val->drawendy = game->sprite[i].height / 2 + game->h / 2;
	if (val->drawendy >= game->h)
		val->drawendy = game->h - 1;
	game->sprite[i].width = abs((int)(game->h / val->transformy));
	val->drawstartx = -game->sprite[i].width / 2 + val->spritescreenx;
	if (val->drawstartx < 0)
		val->drawstartx = 0;
	val->drawendx = game->sprite[i].width / 2 + val->spritescreenx;
	if (val->drawendx >= game->w)
		val->drawendx = game->w - 1;
}

static void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < game->sprite_amt)
	{
		j = -1;
		while (++j < game->sprite_amt - 1)
			if (game->sprite[j].dist < game->sprite[j + 1].dist)
			{
				tmp = game->sprite[j];
				game->sprite[j] = game->sprite[j + 1];
				game->sprite[j + 1] = tmp;
			}
	}
}

static void	get_dist(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->sprite_amt)
		game->sprite[i].dist = ((game->player.posx - game->sprite[i].x) *
								(game->player.posx - game->sprite[i].x) +
								(game->player.posy - game->sprite[i].y) *
								(game->player.posy - game->sprite[i].y));
}

int			draw_sprites_bmp(t_game *game, t_spriteval *val, double *zbuffer)
{
	int	i;

	get_dist(game);
	if (game->sprite_amt > 1)
		sort_sprites(game);
	i = -1;
	while (++i < game->sprite_amt)
	{
		get_sprite_values(game, val, i);
		write_sprite(game, val, zbuffer, i);
	}
	return (0);
}
