/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:38:47 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_d(t_game *game, t_player *player, t_cub cub)
{
	if (player->move_d)
	{
		if (cub.map[(int)(player->posx + player->diry * player->movespeed +
						(player->diry < 0 ? -0.2 : 0.2))]
			[(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx + player->diry * player->movespeed +
						(player->diry < 0 ? -0.2 : 0.2))]
			[(int)(player->posy - 0.2)] == '0')
			player->posx += player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)]
			[(int)(player->posy - player->dirx * player->movespeed -
				(player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy -= player->dirx * player->movespeed;
	}
}

static void	move_a(t_game *game, t_player *player, t_cub cub)
{
	if (player->move_a)
	{
		if (cub.map[(int)(player->posx - player->diry * player->movespeed -
						(player->diry < 0 ? -0.2 : 0.2))]
			[(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx - player->diry * player->movespeed -
						(player->diry < 0 ? -0.2 : 0.2))]
			[(int)(player->posy - 0.2)] == '0')
			player->posx -= player->diry * player->movespeed;
		if (cub.map[(int)(player->posx)]
			[(int)(player->posy + player->dirx * player->movespeed +
				(player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy += player->dirx * player->movespeed;
	}
}

static void	move_s(t_game *game, t_player *player, t_cub cub)
{
	if (player->move_s)
	{
		if (cub.map[(int)(player->posx - player->dirx * player->movespeed -
						(player->dirx < 0 ? -0.2 : 0.2))]
			[(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx - player->dirx * player->movespeed -
						(player->dirx < 0 ? -0.2 : 0.2))]
			[(int)(player->posy - 0.2)] == '0')
			player->posx -= player->dirx * player->movespeed;
		if (cub.map[(int)(player->posx)]
			[(int)(player->posy - player->diry * player->movespeed -
				(player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy -= player->diry * player->movespeed;
	}
}

static void	move_w(t_game *game, t_player *player, t_cub cub)
{
	if (player->move_w)
	{
		if (cub.map[(int)(player->posx + player->dirx * player->movespeed +
						(player->dirx < 0 ? -0.2 : 0.2))]
			[(int)(player->posy + 0.2)] == '0' &&
			cub.map[(int)(player->posx + player->dirx * player->movespeed +
						(player->dirx < 0 ? -0.2 : 0.2))]
			[(int)(player->posy - 0.2)] == '0')
			player->posx += player->dirx * player->movespeed;
		if (cub.map[(int)(player->posx)]
			[(int)(player->posy + player->diry * player->movespeed +
				(player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy += player->diry * player->movespeed;
	}
}

int			move(t_game *game, t_player *player, t_cub cub)
{
	move_w(game, player, cub);
	move_s(game, player, cub);
	move_a(game, player, cub);
	move_d(game, player, cub);
	rot_r(game, player, cub);
	rot_l(game, player, cub);
	return (0);
}
