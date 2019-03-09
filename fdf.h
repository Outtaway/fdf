/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:05 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/09 20:08:53 by kpshenyc         ###   ########.fr       */
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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define _2DPOINT(x_, y_) (t_point_2d){.x = x_, .y = y_}
# define TO_RAD(angle) ((double)((double)(angle) * M_PI / 180.0))
typedef struct		s_point_2d
{
	int32_t			x;
	int32_t			y;
}					t_point_2d;

typedef struct		s_point_3d
{
	int32_t			x;
	int32_t			y;
	int32_t			z;
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
