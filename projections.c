/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:49:49 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/04/16 12:49:51 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int8_t				isometric_proj(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;
	double		prev_x;
	double		prev_y;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			prev_x = fdf->trans_map[i][j].x;
			prev_y = fdf->trans_map[i][j].y;
			fdf->trans_map[i][j].x = ((prev_x - prev_y) * cos(0.523599))
				* fdf->scale + fdf->shift_x;
			fdf->trans_map[i][j].y = ((prev_x + prev_y) * sin(0.523599) -
				fdf->trans_map[i][j].z) * fdf->scale + fdf->shift_y;
		}
	}
	return (1);
}

int8_t				parallel_proj(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;
	double		prev_x;
	double		prev_y;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			prev_x = fdf->trans_map[i][j].x;
			prev_y = fdf->trans_map[i][j].y;
			fdf->trans_map[i][j].x = prev_x * fdf->scale + fdf->shift_x;
			fdf->trans_map[i][j].y = prev_y * fdf->scale + fdf->shift_y;
		}
	}
	return (1);
}

int8_t				perspective_proj(t_fdf *fdf)
{
	set_up_clip_matr(fdf);
	mult_clip_matr_on_points(fdf);
	transform_to_2d(fdf);
	return (1);
}
