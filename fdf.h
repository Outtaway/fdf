/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:05 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/10 00:39:14 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "libftprintf/includes/ft_printf.h"

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define WIN_WIDTH 1500
# define WIN_HEIGHT 800

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
# elif
#  define ESC 63
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
# endif

# define SHIFT_STEP 15
# define ROTATE_STEP 2

# define _2DPOINT(x_, y_) (t_point_2d){.x = x_, .y = y_}
# define TO_RAD(angle) ((double)((double)(angle) * acos(-1.0f) / 180.0))

typedef struct		s_point_2d
{
	int32_t			x;
	int32_t			y;
}					t_point_2d;

typedef struct		s_point_3d
{
	double			x;
	double			y;
	double			z;
}					t_point_3d;

typedef struct		s_cell
{
	int32_t			value;
	int32_t			color;
}					t_cell;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	t_point_3d		**map;
	t_point_3d		**transformed_map;
	t_point_2d		**projected_map;
	int32_t			map_height;
	int32_t			map_width;

	int32_t			scale;
	int32_t			shift_x;
	int32_t			shift_y;

	double			x_rotate;
	double			y_rotate;
	double			z_rotate;

	int32_t			z_modif;

}					t_fdf;

void				read_map(char *file_name, t_fdf *fdf);
int8_t				rotate_x(t_fdf *fdf);
int8_t				rotate_y(t_fdf *fdf);
int8_t				rotate_z(t_fdf *fdf);
void				copy_map(t_fdf *fdf);
#endif
