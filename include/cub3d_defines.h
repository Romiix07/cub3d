/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/22 17:57:56 by rmouduri         ###   ########.fr       */
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

#endif
