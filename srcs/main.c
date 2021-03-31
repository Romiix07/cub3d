/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 16:35:04 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3d.h"
#include "cub3d_defines.h"
#include "cub.h"

static int	display(t_game *game)
{
	move(&game->player, game->cub);
	raycast(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

static int	main_loop(t_game *game)
{
	mlx_hook(game->win, 33, 1L << 17, &exit_all, game);
	mlx_hook(game->win, 2, 1L << 0, &get_key_pressed, game);
	mlx_loop_hook(game->mlx, &display, game);
	mlx_hook(game->win, 3, 1L << 1, &get_key_released, game);
	mlx_loop(game->mlx);
	return (0);
}

int			main(int argc, char **argv)
{
	t_game	game;
	t_cub	cub;

	if (argc < 2)
		return (write(2, "Error\nNot enough arguments\n", 26));
	game.screenshot = 0;
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		game.screenshot = 1;
	if (!cub_parse(argv[1], &cub))
		return (0);
	if (!init_game(&game, &cub))
		return (write(2, "Error\nGame init\n", 17));
	if (game.screenshot)
		return (create_bmp(&game));
	main_loop(&game);
	return (1);
}
