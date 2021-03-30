/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:43:02 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/30 17:48:09 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

static void	get_sprite_amt(t_game *game, t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= cub->y)
	{
		x = -1;
		while (++x <= cub->x)
			if (cub->map[y][x] == '2')
				++game->sprite_amt;
	}
}

static int	get_sprites(t_game *game, t_cub *cub)
{
	int	x;
	int	y;
	int	i;

	if (!(game->sprite_tex.img = mlx_xpm_file_to_image(game->mlx, cub->sprite,
							&game->sprite_tex.width, &game->sprite_tex.height)))
		return (0);
	game->sprite_tex.addr = mlx_get_data_addr(game->sprite_tex.img,
					&game->sprite_tex.bpp,
					&game->sprite_tex.line_length, &game->sprite_tex.endian);
	if (!(game->sprite = malloc(sizeof(t_sprite) * game->sprite_amt)))
		return (0);
	y = -1;
	i = -1;
	while (++y <= cub->y)
	{
		x = -1;
		while (++x <= cub->x)
			if (cub->map[y][x] == '2')
			{
				game->sprite[++i].y = x;
				game->sprite[i].x = y;
			}
	}
	return (1);
}

static int	get_tex(t_game *g, t_cub *c)
{
	int	i;

	if (!(g->tex = malloc(sizeof(t_img) * 4)))
		return (0);
	i = -1;
	while (++i < 4)
		g->tex[i].img = NULL;
	if (!(g->tex[0].img = mlx_xpm_file_to_image(g->mlx, c->north,
							&g->tex[0].width, &g->tex[0].height)))
		return (0);
	if (!(g->tex[1].img = mlx_xpm_file_to_image(g->mlx, c->south,
							&g->tex[1].width, &g->tex[1].height)))
		return (0);
	if (!(g->tex[2].img = mlx_xpm_file_to_image(g->mlx, c->west,
							&g->tex[2].width, &g->tex[2].height)))
		return (0);
	if (!(g->tex[3].img = mlx_xpm_file_to_image(g->mlx, c->east,
							&g->tex[3].width, &g->tex[3].height)))
		return (0);
	i = -1;
	while (++i < 4)
		g->tex[i].addr = mlx_get_data_addr(g->tex[i].img, &g->tex[i].bpp,
							&g->tex[i].line_length, &g->tex[i].endian);
	return (1);
}

static int	get_values(t_game *game, t_cub *cub)
{
	int i;
	int j;

	i = -1;
	while (++i <= game->cub.y)
	{
		j = -1;
		while (++j <= game->cub.x)
			if (game->cub.map[i][j] == 'N' || game->cub.map[i][j] == 'S' ||
				game->cub.map[i][j] == 'E' || game->cub.map[i][j] == 'W')
				game->cub.map[i][j] = '0';
	}
	game->player.movespeed = 0.15;
	game->player.rotspeed = 0.07;
	game->player.move_w = 0;
	game->player.move_a = 0;
	game->player.move_s = 0;
	game->player.move_d = 0;
	game->player.rot_r = 0;
	game->player.rot_l = 0;
	return (1);
}

int			init_game(t_game *game, t_cub *cub)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->sprite_tex.img = NULL;
	game->sprite = NULL;
	game->tex = NULL;
	game->sprite_amt = 0;
	if (!(game->mlx = mlx_init()))
		return (free_game(game) + free_cub(cub));
	game->cub = *cub;
	get_game(game);
	if (!(game->win = mlx_new_window(game->mlx, game->w, game->h, "Cub3d")))
		return (free_game(game) + free_cub(cub));
	if (!(game->img.img = mlx_new_image(game->mlx, game->w, game->h)))
		return (free_game(game) + free_cub(cub));
	if (!(get_tex(game, cub)))
		return (free_game(game) + free_cub(cub));
	get_sprite_amt(game, cub);
	if (game->sprite_amt)
		if (!(get_sprites(game, cub)))
			return (free_game(game) + free_cub(cub));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
	&game->img.line_length, &game->img.endian);
	return (get_values(game, cub));
}
