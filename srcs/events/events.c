/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:06:37 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:40:51 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_defines.h"

int		exit_all(t_game *game)
{
	free_game(game);
	free_cub(&game->cub);
	exit(0);
}

int		get_key_pressed(int keycode, t_game *game)
{
	if (keycode == LKEY_W)
		game->player.move_w = 1;
	if (keycode == LKEY_A)
		game->player.move_a = 1;
	if (keycode == LKEY_S)
		game->player.move_s = 1;
	if (keycode == LKEY_D)
		game->player.move_d = 1;
	if (keycode == LKEY_RARR)
		game->player.rot_r = 1;
	if (keycode == LKEY_LARR)
		game->player.rot_l = 1;
	if (keycode == LKEY_ESC)
		return (exit_all(game));
	return (0);
}

int		get_key_released(int keycode, t_game *game)
{
	if (keycode == LKEY_W || keycode == LKEY_W)
		game->player.move_w = 0;
	if (keycode == LKEY_A || keycode == LKEY_A)
		game->player.move_a = 0;
	if (keycode == LKEY_S || keycode == LKEY_S)
		game->player.move_s = 0;
	if (keycode == LKEY_D || keycode == LKEY_D)
		game->player.move_d = 0;
	if (keycode == 124 || keycode == LKEY_RARR)
		game->player.rot_r = 0;
	if (keycode == 123 || keycode == LKEY_LARR)
		game->player.rot_l = 0;
	return (0);
}
