/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/29 13:15:21 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

enum	e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

# define LKEY_W		119
# define LKEY_A		97
# define LKEY_S		115
# define LKEY_D		100
# define LKEY_LARR	65361
# define LKEY_RARR	65363
# define LKEY_ESC	65307

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53

# define EVENT_KEYPRESS			2
# define EVENT_KEYRELEASE		3
# define EVENT_MOTIONNOTIFY		6
# define EVENT_DESTROYNOTIFY	17

# define RGB_RED	0xFF0000
# define RGB_GREEN	0x00FF00
# define RGB_BLUE	0x0000FF
# define RGB_WHITE	0xFFFFFF
# define RGB_BLACK	0x000000

# define BMP_HEADER_FIELD	0x4D42
# define BMP_OFFSET			0x36
# define BMP_HEADER_SIZE	0x28
# define BMP_COLOR_PLANES	0x1
# define BMP_BITS_PER_PIXEL	0x18

#endif
