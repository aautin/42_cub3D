/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:41:02 by enorie            #+#    #+#             */
/*   Updated: 2024/07/02 21:26:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "X11/keysym.h"
# include <math.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		sizex;
	int		sizey;
}				t_vars;

typedef struct s_pos
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}				t_pos;

typedef struct s_data
{
	void	*img;
	int		*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_map
{
	t_data		*no;
	t_data		*so;
	t_data		*we;
	t_data		*ea;
	int			f;
	int			c;
	char		**map;
}				t_map;

typedef struct s_raycast
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
	t_data			*texture;
}				t_raycast;

typedef struct s_all
{
	t_map		*map;
	t_pos		*pos;
	t_vars		*vars;
	t_data		*data;
	t_raycast	*rc;
}				t_all;

void	ft_free_numbers(char **numbers);
void	ft_free_all(t_all *all);
int		ft_check_numbers(char **numbers);
int		ft_allnum(char *ligne);
char	**ft_get_map_size(int fd, char *ligne);
int		ft_get_color_numbers(int *colors, char *ligne);
int		ft_get_texture_path(char *ligne, t_vars *vars, t_data *data);
int		key_hook(int keycode, t_all *all);
int		end(t_vars *vars);
int		ft_get_map(int fd, t_map *map, char *ligne, char *path);
int		ft_choose(t_map *map, char *ligne, t_vars *vars);
int		ft_choose2(t_map *map, char *ligne);
void	ft_cubed(t_all *all);
t_data	*ft_find_texture(int side, double raydirx, double raydiry, t_map *map);
int		ft_puterror(char *str);
void	ft_get_dir_n(t_pos *pos);
void	ft_get_dir_e(t_pos *pos);
void	ft_get_dir_w(t_pos *pos);
void	ft_get_dir_s(t_pos *pos);
void	ft_get_pos(char **map, int i, int j, t_pos *pos);
int		ft_create_trgb(int t, int r, int g, int b);
void	ft_raycast1(t_raycast *rc, t_all *all, int x);
void	ft_raycast2(t_raycast *rc, t_pos *pos);
void	ft_raycast3(t_raycast *rc, t_map *map);
void	ft_raycast4(t_raycast *rc, t_all *all);
void	ft_draw(t_raycast *rc, t_all *all, int x);
void	ft_move_up(t_all *all);
void	ft_move_down(t_all *all);
void	ft_move_left(t_all *all);
void	ft_move_right(t_all *all);
void	ft_init_pixels(t_all *all, t_raycast *rc);
t_all	*ft_init_strucks(void);
int		ft_init_map(t_map *map);

#endif
