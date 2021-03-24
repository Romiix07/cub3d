/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:59:42 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:36:28 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "cub3d_defines.h"
#include "cub.h"

void	rot_l(t_game *game, t_player *player, t_cub cub)
{
	double olddirx;
	double oldplanex;

	olddirx = player->dirx;
	oldplanex = player->planex;
	if (player->rot_l)
	{
		player->dirx = player->dirx * cos(player->rotspeed) - player->diry *
			sin(player->rotspeed);
		player->diry = olddirx * sin(player->rotspeed) + player->diry *
			cos(player->rotspeed);
		player->planex = player->planex * cos(player->rotspeed) - player->planey
			* sin(player->rotspeed);
		player->planey = oldplanex * sin(player->rotspeed) + player->planey *
			cos(player->rotspeed);
	}
}

void	rot_r(t_game *game, t_player *player, t_cub cub)
{
	double olddirx;
	double oldplanex;

	olddirx = player->dirx;
	oldplanex = player->planex;
	if (player->rot_r)
	{
		player->dirx = player->dirx * cos(-player->rotspeed) - player->diry *
			sin(-player->rotspeed);
		player->diry = olddirx * sin(-player->rotspeed) + player->diry *
			cos(-player->rotspeed);
		player->planex = player->planex * cos(-player->rotspeed) -
			player->planey * sin(-player->rotspeed);
		player->planey = oldplanex * sin(-player->rotspeed) + player->planey *
			cos(-player->rotspeed);
	}
}
