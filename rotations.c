/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:10:37 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/10 00:27:51 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int8_t		rotate_x(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;
	double		prev_y;
	double		prev_z;

	i = -1;
	double shit = TO_RAD(fdf->x_rotate);
	ft_printf("%f\n", shit);
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			prev_y = fdf->transformed_map[i][j].y - fdf->map_height / 2;
			prev_z = fdf->transformed_map[i][j].z;
			fdf->transformed_map[i][j].y = prev_y * cos(TO_RAD(fdf->x_rotate)) + prev_z * sin(TO_RAD(fdf->x_rotate));
			fdf->transformed_map[i][j].z = -prev_y * sin(TO_RAD(fdf->x_rotate)) + prev_z * cos(TO_RAD(fdf->x_rotate));
		}
	}
	return (1);
}

int8_t		rotate_y(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;
	double		prev_x;
	double		prev_z;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			prev_x = fdf->transformed_map[i][j].x - fdf->map_width / 2;
			prev_z = fdf->transformed_map[i][j].z;
			fdf->transformed_map[i][j].x = prev_x * cos(TO_RAD(fdf->y_rotate)) + prev_z * sin(TO_RAD(fdf->y_rotate));
			fdf->transformed_map[i][j].z = -prev_x * sin(TO_RAD(fdf->y_rotate)) + prev_z * cos(TO_RAD(fdf->y_rotate));
		}
	}
	return (1);
}

int8_t		rotate_z(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;
	double		prev_x;
	double		prev_y;

	i = -1;
	double shit = TO_RAD(fdf->z_rotate);
	ft_printf("%f\n", shit);
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			prev_x = fdf->transformed_map[i][j].x;
			prev_y = fdf->transformed_map[i][j].y;
			fdf->transformed_map[i][j].x = prev_x * cos(TO_RAD(fdf->z_rotate)) - prev_y * sin(TO_RAD(fdf->z_rotate));
			fdf->transformed_map[i][j].y = prev_x * sin(TO_RAD(fdf->z_rotate)) + prev_y * cos(TO_RAD(fdf->z_rotate));
		}
	}
	return (1);
}