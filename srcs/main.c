/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:45:51 by rmouduri         ###   ########.fr       */
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
	move(game, &game->player, game->cub);
	raycast(game, game->cub);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

static int	main_loop(t_game *game)
{
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
		return (write(2, "Error\nInvalid arguments\n", 23));
	if (!cub_parse(argv[1], &cub))
		return (0);
	if (!init_game(&game, &cub))
		return (write(2, "Error\nGame init\n", 17));
	main_loop(&game);
	return (1);
}
