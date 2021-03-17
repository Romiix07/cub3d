/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/17 14:04:50 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3d.h"
#include "cub3d_defines.h"
#include "cub.h"

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

int		move(t_game *game, t_player *player, t_cub cub)
{
	if (player->move_w)
	{
		if (cub.map[(int)(player->posx + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == '0')
			player->posx += player->dirx * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))] == '0')
			player->posy += player->diry * player->movespeed;
	}
	if (player->move_a)
	{
		if (cub.map[(int)(player->posx - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == '0')
			player->posx -= player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy + player->dirx * player->movespeed + (player->dirx < 0 ? - 0.2 : 0.2))] == '0')
			player->posy += player->dirx * player->movespeed;
	}
	if (player->move_s)
	{
		if (cub.map[(int)(player->posx - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == '0')
			player->posx -= player->dirx * player->movespeed;	
		if (cub.map[(int)(player->posx)][(int)(player->posy - player->diry * player->movespeed - (player->diry < 0 ? - 0.2 : 0.2))] == '0')
			player->posy -= player->diry * player->movespeed;
	}
	if (player->move_d)
	{
		if (cub.map[(int)(player->posx + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx + player->diry * player->movespeed + (player->diry < 0 ? - 0.2 : 0.2))][(int)(player->posy - 0.2)] == '0')
			player->posx += player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)][(int)(player->posy - player->dirx * player->movespeed - (player->dirx < 0 ? - 0.2 : 0.2))] == '0')
			player->posy -= player->dirx * player->movespeed;
	}
	if (player->rot_r)
	{
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-player->rotspeed) - player->diry * sin(-player->rotspeed);
		player->diry = oldDirX * sin(-player->rotspeed) + player->diry * cos(-player->rotspeed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(-player->rotspeed) - player->planey * sin(-player->rotspeed);
		player->planey = oldPlaneX * sin(-player->rotspeed) + player->planey * cos(-player->rotspeed);
	}
	if (player->rot_l)
	{
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(player->rotspeed) - player->diry * sin(player->rotspeed);
		player->diry = oldDirX * sin(player->rotspeed) + player->diry * cos(player->rotspeed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(player->rotspeed) - player->planey * sin(player->rotspeed);
		player->planey = oldPlaneX * sin(player->rotspeed) + player->planey * cos(player->rotspeed);	
	}
	return (0);
}

int		get_key_pressed(int keycode, t_game *game)
{
    if (keycode == KEY_W)
		game->player.move_w = 1;
    if (keycode == KEY_A)
		game->player.move_a = 1;
    if (keycode == KEY_S)
		game->player.move_s = 1;
    if (keycode == KEY_D)
		game->player.move_d = 1;
    if (keycode == 124)
		game->player.rot_r = 1;
    if (keycode == 123)
		game->player.rot_l = 1;
	if (keycode == KEY_ESC)
		return (close_window(keycode, game) + exit_all(game));
    return (0);
}

int		get_key_released(int keycode, t_game *game)
{
    if (keycode == KEY_W)
		game->player.move_w = 0;
    if (keycode == KEY_A)
		game->player.move_a = 0;
    if (keycode == KEY_S)
		game->player.move_s = 0;
    if (keycode == KEY_D)
		game->player.move_d = 0;
    if (keycode == 124)
		game->player.rot_r = 0;
    if (keycode == 123)
		game->player.rot_l = 0;
    return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

/*
int		put_image(int keycode, t_game *game)
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
*/

int	draw_vertical_line(t_game *game, int x, int color)
{
	int	y;

	y = game->camera.drawstart;
	mlx_clear_window(game->mlx, game->win);
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

	y = 0;
//	y = game->camera.drawstart;
	while (y < game->h)
	{
		my_mlx_pixel_put(&game->img, x, y, buffer[y]);
		++y;
	}
	return (0);
}

int	tmp(t_game *game)
{
//	printf("posx = %f, posy = %f\n", game->player.posx, game->player.posy);
//	mlx_clear_window(game->mlx, game->win);
//	put_image(0, game);
	move(game, &game->player, game->cub);
	loop(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}

int	**getmap(void)
{
	int **map = malloc(sizeof(int *) * 15);

	for (int i = 0; i < 15; ++i) {
		map[i] = malloc(sizeof(int) * 10);
		for (int j = 0; j < 10; ++j)
		{
			if (i == 0 || i == 14)
				map[i][j] = 1;
			else if (j == 0 || j == 9)
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
	}
	map[2][2] = 1;
	map[2][3] = 1;
	map[2][4] = 1;
	map[3][2] = 1;
	map[3][4] = 1;
	map[4][2] = 1;
	map[4][4] = 1;
	return map;
}

int		main(int argc, char **argv)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, w, h, "J'ai fait STMG me parle pas de maths");
	game.img.img = mlx_new_image(game.mlx, w, h);
	game.img.addr = mlx_get_data_addr(game.img.img,
									  &game.img.bits_per_pixel,
									  &game.img.line_length,
									  &game.img.endian);
	game.tmp.img = mlx_xpm_file_to_image(game.win, "../resources/Texture-nord-256.xpm", &game.tmp.width, &game.tmp.height);
	game.tmp.addr = mlx_get_data_addr(game.tmp.img,
									  &game.tmp.bits_per_pixel, 
									  &game.tmp.line_length,
									  &game.tmp.endian);
	game.player.posx = 4.0;
	game.player.posy = 4.0;
	game.player.dirx = -1.0;
	game.player.diry = 0.0;
	game.player.planex = 0.0;
	game.player.planey = 0.66;
	game.player.movespeed = 0.12;
	game.player.rotspeed = 0.05;
    if (cub_parse("map.cub", &game.cub) == 1)
        write(1, "OUI\n", 4);
	else
	return (0);
	for (int i = 0; i <= game.cub.y; ++i)
		for (int j = 0; j <= game.cub.x; ++j)
			if (game.cub.map[i][j] == 'N')
				game.cub.map[i][j] = '0';
	game.h = h;
	game.w = w;
	if (!(game.buffer = malloc(sizeof(int) * h)))
		return (write(2, "Error Malloc Buffer of h * int\n", 31));
	mlx_hook(game.win, 2, 0, &get_key_pressed, &game);
	mlx_hook(game.win, 3, 0, &get_key_released, &game);
	mlx_loop_hook(game.mlx, &tmp, &game);
	mlx_loop(game.mlx);
	return (0);
}
