/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 14:03:31 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx.h"
# include "cub.h"

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

int				raycast(struct s_game *game, struct s_cub cub);
int				draw_buffer(struct s_game *game, int x, unsigned int *buffer);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
int				exit_all(t_game *game);
int				free_game(t_game *game);
int				free_cub(t_cub *cub);
void			rot_r(t_player *player);
void			rot_l(t_player *player);
int				move(t_player *player, t_cub cub);
int				get_key_released(int keycode, t_game *game);
int				get_key_pressed(int keycode, t_game *game);
void			get_perp_drawstartend(t_game *game, t_player *player,
									t_camera *camera);
int				select_texture(t_game *game);
void			get_wallx_texx(t_player *playr, t_camera *cam, t_img img);
void			fill_line(t_game *game, t_camera *cam, int x, t_img img);
int				free_game(t_game *game);
int				free_tex(t_game *game);
int				free_cub(t_cub *cub);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
int				init_game(t_game *game, t_cub *cub);

#endif
