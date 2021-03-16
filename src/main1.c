/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/15 15:27:23 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3d.h"
#include "cub3d_defines.h"

int h = 1080;
int w = 1920;

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

// JE DONNE UN DOUBLE AU LIEU DUN INT, acorriger

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
//	printf("drawstart = %d, drawend = %d\n", game->camera.drawstart, game->camera.drawend);
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
//	printf("drawstart = %d, drawend = %d\n", game->camera.drawstart, game->camera.drawend);
	mlx_clear_window(game->mlx, game->win);
	game->img.addr = mlx_get_data_addr(game->img.img,
									   &game->img.bits_per_pixel,
									   &game->img.line_length,
									   &game->img.endian);
	while (y < game->camera.drawend)
	{
		my_mlx_pixel_put(&game->img, x, y, buffer[y]);
		++y;
	}
	return (0);
}

int loop1(t_game *game, t_player *player, t_camera *camera, t_cub cub)
{
	int x;
	int mapx;
	int mapy;
	int color;
	int buffer[h];

	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		camera->camerax = 2 * x / (double)w - 1;
		camera->raydirx = player->dirx + player->planex * camera->camerax;
		camera->raydiry = player->diry + player->planey * camera->camerax;
		
		//which box of the map we're in
		mapx = (int)player->posx;
		mapy = (int)player->posy;
		
		//lenght of ray from one current position to next x or y-side
		camera->deltadistx = fabs(1 / camera->raydirx);
		camera->deltadisty = fabs(1 / camera->raydiry);

		//calculate step and initial sidedist
		if (camera->raydirx < 0)
		{
			camera->stepx = -1;
			camera->sidedistx = (player->posx - mapx) * camera->deltadistx;
		}
		else
		{
			camera->stepx = 1;
			camera->sidedistx = (mapx + 1.0 - player->posx) * camera->deltadistx;
		}
		if (camera->raydiry < 0)
		{
			camera->stepy = -1;
			camera->sidedisty = (player->posy - mapy) * camera->deltadisty;
		}
		else
		{
			camera->stepy = 1;
			camera->sidedisty = (mapy + 1.0 - player->posy) * camera->deltadisty;
		}

		//perform DDA
		camera->hit = 0;
		while (camera->hit == 0)
		{
			if (camera->sidedistx < camera->sidedisty)
			{
				camera->sidedistx += camera->deltadistx;
				mapx += camera->stepx;
				camera->side = 0;
			}
			else
			{
				camera->sidedisty += camera->deltadisty;
				mapy += camera->stepy;
				camera->side = 1;
			}
			if (cub.map[mapx][mapy] > 0)
				camera->hit = 1;
		}

		//calculate distance projected on camera direction (euclidean distance will give fisheye effect)
		if (camera->side == 0)
			camera->perpwalldist = (mapx - player->posx + (1 - camera->stepx) /
									2) / camera->raydirx;
		else
			camera->perpwalldist = (mapy - player->posy + (1 - camera->stepy) /
									2) / camera->raydiry;

		//calculate height of line to draw on screen, h == window size
		camera->lineheight = (int)(h / camera->perpwalldist);

//		printf("ll = %d, ppw = %f\n", camera->lineheight, camera->perpwalldist);
		//calculate lowest and highest pixel to fill in current stripe
		camera->drawstart = -camera->lineheight / 2 + h / 2;
		if (camera->drawstart < 0)
			camera->drawstart = 0;
		camera->drawend = camera->lineheight / 2 + h / 2;
		if (camera->drawend >= h)
			camera->drawend = h - 1;

		//get color
		if (mapy > player->posy && camera->side == 1)
//            curr_img = game->img[1];
			color = RGB_GREEN;
        else if (mapx > player->posx && camera->side == 0)
//            curr_img = game->img[2];
			color = RGB_RED;
        else if (mapy < player->posy && camera->side == 1)
//            curr_img = game->img[3];
			color = RGB_BLUE;
        else
			color = RGB_WHITE;
//            curr_img = game->img[4];
		if (cub.map[mapx][mapy] == 1)
			color = RGB_BLUE;
		else
			color = RGB_RED;
		if (camera->side == 1)
		color /= 2;

		double wallx;
		if (camera->side == 0)
			wallx = player->posy + camera->perpwalldist * camera->raydiry;
		else
			wallx = player->posx + camera->perpwalldist * camera->raydirx;
		wallx -= wallx < 0 ? (int)wallx - 1 : (int)wallx;

		int texx = (int)(wallx * (double)game->tmp.width);
		if (camera->side == 0 && camera->raydirx > 0)
			texx = game->tmp.width - texx - 1;
		if (camera->side == 1 && camera->raydiry < 0)
			texx = game->tmp.width - texx - 1;

		double step = 1.0 * game->tmp.height / camera->lineheight;
		double texpos = (camera->drawstart - h / 2 + camera->lineheight / 2) * step;

		for (int y = camera->drawstart; y < camera->drawend; ++y)
		{
			int texy = (int)texpos & (game->tmp.height - 1);
			texpos += step;
//			buffer[y] = RGB_RED;
			buffer[y] = *(int *)(game->tmp.addr + (texy * game->tmp.line_length + texx * (game->tmp.bits_per_pixel / 8)));
		}
		draw_buffer(game, x, buffer);
//		draw_vertical_line(game, x, color);
		++x;
	}
	return (1);
}

int	tmp(int keycode, t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	put_image(0, game);
	key_pressed(keycode, game, &game->player, game->cub);
//	printf("posx = %f, posy = %f\n", game->player.posx, game->player.posy);
	loop1(game, &game->player, &game->camera, game->cub);
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
//	mlx_hook(game.win, 2, 1L<<0, key_pressed, &game);
	mlx_hook(game.win, 2, 1L<<0, &tmp, &game);
	mlx_hook(game.win, 17, 0, &exit_all, &game);
	mlx_loop(game.mlx);
	return (0);
}
