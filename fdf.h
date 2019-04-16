/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:05 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/11 09:49:27 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "libftprintf/includes/ft_printf.h"
# include <sys/errno.h>

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define MAX_COLORS 4

# define WIN_WIDTH 1500
# define WIN_HEIGHT 700

# ifdef __linux__
#  define ESC 65307
#  define NUM4 65430
#  define NUM8 65431
#  define NUM6 65432
#  define NUM2 65433
#  define MINUS 45
#  define PLUS 61
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define C_KEY 99
# else
#  define ESC 53
#  define NUM7 89
#  define NUM9 92
#  define NUM4 86
#  define NUM8 91
#  define NUM6 88
#  define NUM2 84
#  define MINUS 27
#  define PLUS 24
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define C_KEY 8
#  define P_KEY 35
#  define F_KEY 3
#  define G_KEY 5
#  define N_KEY 45
#  define M_KEY 46
#  define R_KEY 15
# endif

# define SHIFT_STEP 5
# define ROTATE_STEP 2

# define _2DPOINT(x_, y_) (t_point_2d){.x = x_, .y = y_}
# define TO_RAD(angle) ((double)((double)(angle) * acos(-1.0f) / 180.0))
# define TRMAP(i, j) (fdf->trans_map[i][j])
# define CLMP(i) (fdf->clip_matr[i])
# define ERROR_EXIT(msg) { write(2, msg, ft_strlen(msg)); exit(EXIT_FAILURE); }
# define CL_ROT { fdf->x_rotate = 0; fdf->y_rotate = 0; fdf->z_rotate = 0; }

enum	e_projection_type {
	ISOMETRIC, PARALLEL, PERSPECTIVE
};

typedef struct		s_point_2d
{
	int32_t			x;
	int32_t			y;
	double			w;
}					t_point_2d;

typedef struct		s_point_3d
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_point_3d;

typedef struct		s_cell
{
	int32_t			value;
	int32_t			color;
}					t_cell;

typedef struct		s_camera
{
	double			fov;
	double			aspect_ratio;
	double			far;
	double			near;
}					t_camera;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	int32_t			bpp;
	int32_t			size_line;
	int32_t			endian;
	void			*img;
	char			*img_data;
	t_point_3d		**map;
	t_point_3d		**trans_map;
	int32_t			map_height;
	int32_t			map_width;

	int32_t			scale;
	int32_t			shift_x;
	int32_t			shift_y;
	double			x_rotate;
	double			y_rotate;
	double			z_rotate;
	int8_t			(*projections[3])(struct s_fdf*);
	int8_t			projection;
	t_camera		camera;
	double			clip_matr[16];

}					t_fdf;

int8_t				isometric_proj(t_fdf *fdf);
int8_t				parallel_proj(t_fdf *fdf);
int8_t				perspective_proj(t_fdf *fdf);

void				read_map(char *file_name, t_fdf *fdf);
void				init_fdf(t_fdf *fdf);
int8_t				rotate_x(t_fdf *fdf);
int8_t				rotate_y(t_fdf *fdf);
int8_t				rotate_z(t_fdf *fdf);
void				set_up_clip_matr(t_fdf *fdf);
void				mult_clip_matr_on_points(t_fdf *fdf);
void				transform_to_2d(t_fdf *fdf);

int8_t				rotations_keys(int key, t_fdf *fdf);
int8_t				scale_or_colors_keys(int key, t_fdf *fdf);
int8_t				shift_keys(int key, t_fdf *fdf);
void				copy_map(t_fdf *fdf);

#endif
