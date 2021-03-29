/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:25:49 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/29 15:35:37 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_defines.h"

void	fill_line_bmp(t_game *game, t_camera *cam, int x, t_img img)
{
	int	y;

	y = -1 + (x - x);
	while (++y < cam->drawstart)
		my_mlx_pixel_put_bmp(game->fd, game->cub.ceiling_color);
	cam->step = 1.0 * img.height / cam->lineheight;
	cam->texpos = (cam->drawstart - game->h / 2 + cam->lineheight / 2) *
		cam->step;
	while (y < cam->drawend)
	{
		cam->texy = (int)cam->texpos & (img.height - 1);
		cam->texpos += cam->step;
		my_mlx_pixel_put_bmp(game->fd, *(int *)(img.addr +
											(cam->texy *
											img.line_length +
											cam->texx *
											(img.bpp /
											8))));
		++y;
	}
	while ((++y - 1) < game->h)
		my_mlx_pixel_put_bmp(game->fd, game->cub.floor_color);
}
