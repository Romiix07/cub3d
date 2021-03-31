/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:52:06 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 13:55:40 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_put_color(t_game *g, unsigned int *color)
{
	if (((g->camera.texy * (g->sprite_tex.line_length / (g->sprite_tex.bpp / 8))
		+ g->camera.texx) * (g->sprite_tex.bpp / 8)) >=
		(g->sprite_tex.width) * (g->sprite_tex.height) * 4 || g->camera.texy *
		g->sprite_tex.line_length + g->camera.texx < 0)
		return (0);
	*color = *(unsigned int *)(g->sprite_tex.addr + ((g->camera.texy *
		(g->sprite_tex.line_length / (g->sprite_tex.bpp / 8))
		+ g->camera.texx) * (g->sprite_tex.bpp / 8)));
	return (1);
}
