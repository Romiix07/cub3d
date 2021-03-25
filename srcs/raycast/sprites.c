/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:05:59 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/25 14:48:01 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub3d_defines.h"

int draw_sprites(t_game *game, double *zbuffer)
{
	t_sprite	tmp;
	for (int i = 0; i < game->sprite_amt; ++i)
		game->sprite[i].dist = ((game->player.posx - game->sprite[i].x) *
								(game->player.posx - game->sprite[i].x) +
								(game->player.posy - game->sprite[i].y) *
								(game->player.posy - game->sprite[i].y));
	tmp = game->sprite[0];
	if (tmp.dist < game->sprite[1].dist)
	{
		game->sprite[0] = game->sprite[1];
		game->sprite[1] = tmp;
	}
	for (int i = 0; i < game->sprite_amt; ++i)
	{
		double spritex = game->sprite[i].x - game->player.posx;
		double spritey = game->sprite[i].y - game->player.posy;

		double invdet = 1.0 / (game->player.planex * game->player.diry - game->player.dirx * game->player.planey);
		double transformx = invdet * (game->player.diry * spritex - game->player.dirx * spritey);
		double transformy = invdet * (-game->player.planey * spritex + game->player.planex * spritey);

		int spritescreenx = (int)((game->w / 2) * (1 + transformx / transformy));
		
		game->sprite[i].height = abs((int)(game->h / (transformy)));
		
		int drawstarty = -game->sprite[i].height / 2 + game->h / 2;
		if (drawstarty < 0)
			drawstarty = 0;
		int drawendy = game->sprite[i].height / 2 + game->h / 2;
		if (drawendy >= game->h)
			drawendy = game->h - 1;

		game->sprite[i].width = abs((int)(game->h / transformy));

		int drawstartx = -game->sprite[i].width / 2 + spritescreenx;
		if (drawstartx < 0)
			drawstartx = 0;
		int drawendx = game->sprite[i].width / 2 + spritescreenx;
		if (drawendx >= game->w)
			drawendx = game->w - 1;

		for (int stripe = drawstartx; stripe < drawendx; stripe++)
		{
			int texx = (int)(256 * (stripe - (-game->sprite[i].width / 2 + spritescreenx)) * game->sprite_tex.width / game->sprite[i].width) / 256;
			if (transformy > 0 && stripe > 0 && stripe < game->w && transformy < zbuffer[stripe])
				for (int y = drawstarty; y < drawendy; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - game->h * 128 + game->sprite[i].height * 128; //256 and 128 factors to avoid floats
					int texy = ((d * game->sprite_tex.height) / game->sprite[i].height) / 256;
					unsigned int color = *(unsigned int *)(game->sprite_tex.addr +
													(texy *
													game->sprite_tex.line_length +
													texx *
													(game->sprite_tex.bpp /
													 8))); //get current color from the texture
			//					if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&game->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
	return (0);
}
