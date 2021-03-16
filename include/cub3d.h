/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/16 13:27:45 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
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

typedef struct	s_cub {
	int	**map;
}				t_cub;

typedef struct	s_game {
	void		*mlx;
	void		*win;
	int			tab_x_size;
	int			*buffer;
	int			h;
	int			w;
	t_img		img;
	t_img tmp; //temporaire, texture a afficher
	t_player	player;
	t_camera	camera;
	t_cub		cub;
}				t_game;

int	loop(struct s_game *game, struct s_cub cub);
int draw_buffer(struct s_game *game, int x, int *buffer);

#endif
