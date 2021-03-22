/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/22 18:26:44 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	write(1, "O", 1);
    if (keycode == KEY_W || keycode == LKEY_W)
		game->player.move_w = 1;
    if (keycode == KEY_A || keycode == LKEY_A)
		game->player.move_a = 1;
    if (keycode == KEY_S || keycode == LKEY_S)
		game->player.move_s = 1;
    if (keycode == KEY_D || keycode == LKEY_D)
		game->player.move_d = 1;
    if (keycode == 124 || keycode == LKEY_RARR)
		game->player.rot_r = 1;
    if (keycode == 123 || keycode == LKEY_LARR)
		game->player.rot_l = 1;
	if (keycode == KEY_ESC || keycode == LKEY_ESC)
		return (exit_all(game));
    return (0);
}

int		get_key_released(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == LKEY_W)
		game->player.move_w = 0;
    if (keycode == KEY_A || keycode == LKEY_A)
		game->player.move_a = 0;
    if (keycode == KEY_S || keycode == LKEY_S)
		game->player.move_s = 0;
    if (keycode == KEY_D || keycode == LKEY_D)
		game->player.move_d = 0;
    if (keycode == 124 || keycode == LKEY_RARR)
		game->player.rot_r = 0;
    if (keycode == 123 || keycode == LKEY_LARR)
		game->player.rot_l = 0;
    return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
    char	*dst; 

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

int		display(t_game *game)
{
	write(1, "1", 1);
	move(game, &game->player, game->cub);
//	printf("posx = %f, posy = %f\n", game->player.posx, game->player.posy);
	raycast(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return 0;
}

int		free_tex(t_game *g)
{
	int	i = -1;

	if (g->tex)
	{
		while (++i < 4)
		{
			if (g->tex[i].img)
				free(g->tex[i].img);
			else
				break ;
		}
		free(g->tex);
	}
	return (0);
}

int		free_game(t_game *game)
{
	int	i;

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	i = -1;
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx)
		free(game->mlx);
	free_tex(game);
	return (0);
}

int		free_cub(t_cub *cub)
{
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
									 "Merci Christophe, mais fais un effort")))
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
	return (1);
}

int		exit_all(t_game *game)
{
	free_game(game);
	free_cub(&game->cub);
	exit (0);
}

int		main_loop(t_game *game)
{
	mlx_hook(game->win, 2, 0, &get_key_pressed, game);
	mlx_hook(game->win, 3, 0, &get_key_released, game);
	mlx_loop_hook(game->mlx, &display, game);
	mlx_loop(game->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game	game;
	t_cub	cub;

	if (argc < 2)
		return (write(2, "Error\nInvalid arguments\n", 23));
	if (!cub_parse(argv[1], &cub))
		return (0);
	if (!init_game(&game, &cub))
		return (write(2, "Error\nGame init\n", 17));
	main_loop(&game);
	return (1);
}
