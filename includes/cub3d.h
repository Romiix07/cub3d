/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:11:34 by rmouduri          #+#    #+#             */
/*   Updated: 2021/04/04 16:53:28 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx.h"
# include "cub.h"

typedef struct	s_sprite_values {
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		drawstartx;
	int		drawendx;
	int		drawstarty;
	int		drawendy;
}				t_spriteval;

typedef struct	s_sprite {
	int		height;
	int		width;
	int		x;
	int		y;
	double	dist;
}				t_sprite;

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
	char			screenshot;
	int				sprite_amt;
	int				fd;
	int				h;
	int				w;
	t_img			*tex;
	t_img			sprite_tex;
	t_img			img;
	t_sprite		*sprite;
	t_spriteval		spriteval;
	t_player		player;
	t_camera		camera;
	t_cub			cub;
}				t_game;

int				raycast(t_game *game, t_cub cub);
int				draw_buffer(t_game *game, int x, unsigned int *buffer);
int				exit_all(t_game *game);
int				free_game(t_game *game);
int				free_cub(t_cub *cub);
void			rot_r(t_player *player);
void			rot_l(t_player *player);
void			get_game(t_game *game);
int				move(t_player *player, t_cub cub);
int				get_key_released(int keycode, t_game *game);
int				get_key_pressed(int keycode, t_game *game);
void			get_perp_drawstartend(t_game *game, t_player *player,
									t_camera *camera);
int				select_texture(t_game *game);
void			get_wallx_texx(t_player *playr, t_camera *cam, t_img img);
void			fill_line(t_game *game, t_camera *cam, int x, t_img img);
void			cub_init(t_cub *cub);
int				free_parse(t_cub *cub);
int				free_game(t_game *game);
int				free_cub(t_cub *cub);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
int				init_game(t_game *game, t_cub *cub);
int				draw_sprites(t_game *game, t_spriteval *val, double *zbuffer);
int				create_bmp(t_game *game);
int				get_shadow(int color, t_game *game, int x, int y);
int				ft_memdel(char **s, int fd);
int				map_check_loop(t_cub *cub, int i, int j);
int				core(int **map, int i, int j, int x);
int				border(int **map, int i, int j, int x);
int				get_put_color(t_game *g, unsigned int *color);
int				ft_strncmp(char *s1, char *s2, unsigned int n);

#endif
