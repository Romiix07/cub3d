/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/16 14:02:47 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3d.h"
#include "cub3d_defines.h"

int h = 1000;
int w = 1500;

int		exit_all(t_game *game)
{
	exit(0);
	return (0);
}

int		close_window(int keycode, t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	return (0);
}

int		key_pressed(int keycode, t_game *game, t_player *player, t_cub cub)
{
	if (keycode == KEY_W)
	{
		if (cub.map[(int)(player->posx + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == 0 &&
			cub.map[(int)(player->posx + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == 0)
			player->posx += player->dirx * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))] == 0)
			player->posy += player->diry * player->movespeed;
	}
	if (keycode == KEY_A)
	{
		if (cub.map[(int)(player->posx - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == 0 &&
			cub.map[(int)(player->posx - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == 0)
			player->posx -= player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))] == 0)
			player->posy += player->dirx * player->movespeed;
	}
	if (keycode == KEY_S)
	{
		if (cub.map[(int)(player->posx - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == 0 &&
			cub.map[(int)(player->posx - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == 0)
			player->posx -= player->dirx * player->movespeed;	
		if (cub.map[(int)(player->posx)][(int)(player->posy - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))] == 0)
			player->posy -= player->diry * player->movespeed;
	}
	if (keycode == KEY_D)
	{
		if (cub.map[(int)(player->posx + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == 0 &&
			cub.map[(int)(player->posx + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == 0)
			player->posx += player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))] == 0)
			player->posy -= player->dirx * player->movespeed;
	}
	if (keycode == 124)
	{
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-player->rotspeed) - player->diry * sin(-player->rotspeed);
		player->diry = oldDirX * sin(-player->rotspeed) + player->diry * cos(-player->rotspeed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(-player->rotspeed) - player->planey * sin(-player->rotspeed);
		player->planey = oldPlaneX * sin(-player->rotspeed) + player->planey * cos(-player->rotspeed);
	}
	if (keycode == 123)
	{
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(player->rotspeed) - player->diry * sin(player->rotspeed);
		player->diry = oldDirX * sin(player->rotspeed) + player->diry * cos(player->rotspeed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(player->rotspeed) - player->planey * sin(player->rotspeed);
		player->planey = oldPlaneX * sin(player->rotspeed) + player->planey * cos(player->rotspeed);	
	}
	else if (keycode == KEY_ESC)
		return (close_window(keycode, game) + exit_all(game));
	return (0);
}

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int put_image(int keycode, t_game *game)
{
	int a;
	int b;
	int color;

	a = -1;
	color = 0x000000;
	mlx_clear_window(game->mlx, game->win);
	game->img.addr = mlx_get_data_addr(game->img.img,
									   &game->img.bits_per_pixel,
									   &game->img.line_length,
									   &game->img.endian);
	while (++a < w)
	{
		b = -1;
		while (++b < h)
			my_mlx_pixel_put(&game->img, a, b, color);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	draw_vertical_line(t_game *game, int x, int color)
{
	int	y;

	y = game->camera.drawstart;
	mlx_clear_window(game->mlx, game->win);
	game->img.addr = mlx_get_data_addr(game->img.img,
									   &game->img.bits_per_pixel,
									   &game->img.line_length,
									   &game->img.endian);
	while (y < game->camera.drawend)
	{
		my_mlx_pixel_put(&game->img, x, y, color);
		++y;
	}
	return (0);
}

int	draw_buffer(t_game *game, int x, int *buffer)
{
	int	y;

	y = game->camera.drawstart;
//	mlx_clear_window(game->mlx, game->win);
	while (y < game->camera.drawend)
	{
		my_mlx_pixel_put(&game->img, x, y, buffer[y]);
		++y;
	}
	return (0);
}

int	tmp(int keycode, t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	put_image(0, game);
	key_pressed(keycode, game, &game->player, game->cub);
	printf("posx = %f, posy = %f\n", game->player.posx, game->player.posy);
	loop(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}

int	**getmap(void)
{
	int **map = malloc(sizeof(int *) * 10);

	for (int i = 0; i < 10; ++i) {
		map[i] = malloc(sizeof(int) * 10);
		for (int j = 0; j < 10; ++j)
		{
			if (i == 0 || i == 9)
				map[i][j] = 1;
			else if (j == 0 || j == 9)
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
	}
	map[2][2] = 1;
//	map[2][3] = 1;
//	map[2][4] = 1;
//	map[3][2] = 1;
	map[3][4] = 1;
//	map[4][2] = 1;
	map[4][4] = 1;
	return map;
}

int		main(int argc, char **argv)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, w, h, "J'ai fait STMG me parle pas de maths");
	game.img.img = mlx_new_image(game.mlx, w, h);

	game.tmp.img = mlx_xpm_file_to_image(game.win, "../resources/Texture-nord-256.xpm", &game.tmp.width, &game.tmp.height);
	game.tmp.addr = mlx_get_data_addr(game.tmp.img, &game.tmp.bits_per_pixel, &game.tmp.line_length,
									 &game.tmp.endian);
	game.tab_x_size = 10;
	game.player.posx = 6.0;
	game.player.posy = 6.0;
	game.player.dirx = -1.0;
	game.player.diry = 0.0;
	game.player.planex = 0.0;
	game.player.planey = 0.66;
	game.player.movespeed = 0.2;
	game.player.rotspeed = 0.1;
	game.cub.map = getmap();
	game.h = h;
	game.w = w;
	game.img.addr = mlx_get_data_addr(game.img.img,
									   &game.img.bits_per_pixel,
									   &game.img.line_length,
									   &game.img.endian);
	if (!(game.buffer = malloc(sizeof(int) * h)))
		return (write(2, "Error Malloc Buffer of h * int\n", 31));
//	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 2, 1L << 0, &tmp, &game);
	mlx_hook(game.win, 17, 0, &exit_all, &game);
	mlx_loop(game.mlx);
	return (0);
}
