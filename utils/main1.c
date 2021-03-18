
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/18 14:05:38 by rmouduri         ###   ########.fr       */
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

int		exit_all(t_game *game);

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
		return (exit_all(game));
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
    char	*dst;

//	printf("color = %0x\n", (unsigned int)color);
    dst = (img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
    *(unsigned int *)dst = color;
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

/*
int	draw_buffer(t_game *game, int x, unsigned int *buffer)
{
	int	y;

	y = 0;
	while (y < game->h)
	{
		my_mlx_pixel_put(&game->img, x, y, buffer[y]);
		++y;
	}
	return (0);
}
*/

int	loop(t_game *game)
{
	move(game, &game->player, game->cub);
//	printf("posx = %f, posy = %f\n", game->player.posx, game->player.posy);
	raycast(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}

int		free_game(t_game *game)
{
	int	i;

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	i = -1;
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->tmp.img)
		mlx_destroy_image(game->mlx, game->tmp.img);
	if (game->mlx)
		free(game->mlx);
	return (0);
}

int		free_cub(t_cub *cub)
{
	if (cub->str)
		free(cub->str);
	if (cub->north)
		free(cub->north);
	if (cub->east)
		free(cub->east);
	if (cub->west)
		free(cub->west);
	if (cub->south)
		free(cub->south);
	if (cub->sprite)
		free(cub->sprite);
	if (cub->map)
	{
		while ((--cub->y + 1) > 0)
			free(cub->map[cub->y + 1]);
		free(cub->map);
	}
	return (0);
}

int		init_game(t_game *game, t_cub *cub)
{
	if (!(game->mlx = mlx_init()))
		return (free_game(game));
	if (!(game->win = mlx_new_window(game->mlx, cub->res_x, cub->res_y, "cub3d")))
		return (free_game(game));
	if (!(game->img.img = mlx_new_image(game->mlx, cub->res_x, cub->res_y)))
		return (free_game(game));
	if (!(game->tmp.img = mlx_xpm_file_to_image(game->win, "../resources/redbrick.xpm", &game->tmp.width, &game->tmp.height)))
		return (write(2, "Error\nOpening xpm file\n", 23));
	game->tmp.addr = mlx_get_data_addr(game->tmp.img,
									  &game->tmp.bits_per_pixel, 
									  &game->tmp.line_length,
									  &game->tmp.endian);
	game->img.addr = mlx_get_data_addr(game->img.img,
									  &game->img.bits_per_pixel,
									  &game->img.line_length,
									  &game->img.endian);
	game->h = cub->res_y;
	game->w = cub->res_x;
	game->cub = *cub;
	for (int i = 0; i <= game->cub.y; ++i)
		for (int j = 0; j <= game->cub.x; ++j)
			if (game->cub.map[i][j] == 'N')
				game->cub.map[i][j] = '0';
	game->player.posx = 4.0;
	game->player.posy = 4.0;
	game->player.dirx = -1.0;
	game->player.diry = 0.0;
	game->player.planex = 0.0;
	game->player.planey = 0.66;
	game->player.movespeed = 0.12;
	game->player.rotspeed = 0.05;
	return (1);
}

int		exit_all(t_game *game)
{
	free_game(game);
	free_cub(&game->cub);
	exit (0);
}

int tmp(t_game *game)
{
	mlx_hook(game->win, 2, 0, &get_key_pressed, game);
	mlx_hook(game->win, 3, 0, &get_key_released, game);
	mlx_loop_hook(game->mlx, &loop, game);
	mlx_loop(game->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game	game;
	t_cub	cub;

	if (argc < 2)
		return (write(2, "Error\nInvalid arguments count\n", 30));
	if (!cub_parse(argv[1], &cub))
		return (write(1, "Error\nCub parse\n", 17));
	if (!init_game(&game, &cub))
		return (write(1, "Error\nGame init\n", 17));
	tmp(&game);
	return (1);
}
