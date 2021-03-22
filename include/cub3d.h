/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/22 14:15:49 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "../utils/cub.h"
# include "../utils/get_next_line.h"

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_player {
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	movespeed;
	double	rotspeed;
	char	move_w;
	char	move_a;
	char	move_s;
	char	move_d;
	char	rot_l;
	char	rot_r;
}				t_player;

typedef struct	s_camera {
	double	time;
	double	oldtime;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
	double	step;
	double	texpos;
	int		texx;
	int		texy;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_camera;

typedef struct	s_game {
	void			*mlx;
	void			*win;
	int				h;
	int				w;
	t_img			*tex;
	t_img			img;
	t_player		player;
	t_camera		camera;
	t_cub			cub;
}				t_game;

int		raycast(struct s_game *game, struct s_cub cub);
int		draw_buffer(struct s_game *game, int x, unsigned int *buffer);
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);

#endif
