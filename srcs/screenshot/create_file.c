/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:00:54 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/29 15:39:46 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"
#include "cub3d_defines.h"

static int	write_core_header(t_game *game, int fd)
{
	int	val;
	int	i;

	val = BMP_HEADER_SIZE;
	if ((write(fd, &val, sizeof(int))) < 0)
		return (0);
	val = game->w;
	if ((write(fd, &val, sizeof(int))) < 0)
		return (0);
	val = game->h;
	if ((write(fd, &val, sizeof(int))) < 0)
		return (0);
	val = BMP_COLOR_PLANES;
	if ((write(fd, &val, sizeof(short))) < 0)
		return (0);
	val = BMP_BITS_PER_PIXEL;
	if ((write(fd, &val, sizeof(short))) < 0)
		return (0);
	i = -1;
	val = 0;
	while (++i < 6)
		if ((write(fd, &val, sizeof(int))) < 0)
			return (0);
	return (1);
}

static int	write_header(t_game *game, int fd)
{
	int	val;

	val = BMP_HEADER_FIELD;
	if ((write(fd, &val, sizeof(char) * 2)) < 0)
		return (0);
	val = 14 + BMP_HEADER_SIZE + game->w * game->h * BMP_BITS_PER_PIXEL;
	if (write(fd, &val, sizeof(int)) < 0)
		return (0);
	val = 0;
	if ((write(fd, &val, sizeof(int))) < 0)
		return (0);
	val = BMP_OFFSET;
	if ((write(fd, &val, sizeof(int))) < 0)
		return (0);
	return (1);
}

int			create_bmp(t_game *game)
{
	if (!(game->fd = open("screenshot.bmp", O_CREAT | O_APPEND | O_WRONLY |
						O_TRUNC)))
	{
		return (write(2, "Error\nCan't create \"screenshot.bmp\"\n", 36) +
				exit_all(game));
	}
	if (!(write_header(game, game->fd)))
	{
		close(game->fd);
		return (write(2, "Error\nWrite Header\n", 19) + exit_all(game));
	}
	if (!(write_core_header(game, game->fd)))
	{
		close(game->fd);
		return (write(2, "Error\nWrite Core Header\n", 24) + exit_all(game));
	}
	if (!(raycast(game, game->cub)))
	{
		close(game->fd);
		return (write(2, "Error\nWrite Image\n", 18) + exit_all(game));
	}
	close(game->fd);
	return (exit_all(game));
}
