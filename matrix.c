/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:35 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/04/01 19:20:57 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mult_clip_matr_on_points(t_fdf *fdf)
{
	int8_t			i;
	int8_t			j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->trans_map[i][j].x = TRMAP(i, j).x * CLMP(0)
			+ TRMAP(i, j).y * CLMP(4) +
			TRMAP(i, j).z * CLMP(8) + TRMAP(i, j).w * CLMP(12);
			TRMAP(i, j).y = TRMAP(i, j).x * CLMP(1)
			+ TRMAP(i, j).y * CLMP(5) + TRMAP(i, j).z * CLMP(9) + TRMAP(i, j).w
			* CLMP(13);
			TRMAP(i, j).z = TRMAP(i, j).x * CLMP(2)
			+ TRMAP(i, j).y * CLMP(6) +
			TRMAP(i, j).z * CLMP(10) +
			TRMAP(i, j).w * CLMP(14);
			TRMAP(i, j).w = TRMAP(i, j).x * CLMP(3)
			+ TRMAP(i, j).y * CLMP(7) +
			TRMAP(i, j).z * CLMP(11) +
			TRMAP(i, j).w * CLMP(15);
		}
	}
}

void	transform_to_2d(t_fdf *fdf)
{
	int8_t			i;
	int8_t			j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->trans_map[i][j].x = ((fdf->trans_map[i][j].x *
			(double)WIN_WIDTH)) / (2.0 * fdf->trans_map[i][j].w) +
			(double)(WIN_WIDTH / 2);
			fdf->trans_map[i][j].y = ((fdf->trans_map[i][j].y *
			(double)WIN_HEIGHT)) / (2.0 * fdf->trans_map[i][j].w) +
			(double)(WIN_HEIGHT / 2);
		}
	}
}

void	set_up_clip_matr(t_fdf *fdf)
{
	double f;

	ft_memset(fdf->clip_matr, 0, sizeof(double) * 16);
	fdf->clip_matr[0] = 1.0;
	fdf->clip_matr[5] = 1.0;
	fdf->clip_matr[10] = 1.0;
	fdf->clip_matr[15] = 1.0;
	f = 1.0 / tan(TO_RAD(fdf->camera.fov) * 0.5);
	fdf->clip_matr[0] = f * fdf->camera.aspect_ratio;
	fdf->clip_matr[5] = f;
	fdf->clip_matr[10] = (fdf->camera.far + fdf->camera.near) /
		(fdf->camera.far - fdf->camera.near);
	fdf->clip_matr[11] = 1.0;
	fdf->clip_matr[14] = (2.0 * fdf->camera.near * fdf->camera.far) /
						(fdf->camera.near - fdf->camera.far);
	fdf->clip_matr[15] = 0.0;
}
