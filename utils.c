/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:07:30 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/04/16 13:07:32 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

extern int32_t		g_color;

int8_t		rotations_keys(int key, t_fdf *fdf)
{
	if (key == NUM8)
		fdf->x_rotate += ROTATE_STEP;
	else if (key == NUM2)
		fdf->x_rotate -= ROTATE_STEP;
	else if (key == NUM6)
		fdf->y_rotate += ROTATE_STEP;
	else if (key == NUM4)
		fdf->y_rotate -= ROTATE_STEP;
	else if (key == NUM7)
		fdf->z_rotate += ROTATE_STEP;
	else if (key == NUM9)
		fdf->z_rotate -= ROTATE_STEP;
	if (key == NUM2 || key == NUM8 || key == NUM6 || key == NUM4 || key == NUM7
		|| key == NUM9)
		return (1);
	return (0);
}

int8_t		scale_or_colors_keys(int key, t_fdf *fdf)
{
	if (key == PLUS && (fdf->projection == ISOMETRIC ||
		fdf->projection == PARALLEL))
		fdf->scale += 5;
	else if (key == PLUS && fdf->projection == PERSPECTIVE)
		fdf->camera.fov < 115 ? fdf->camera.fov += 5 : 0;
	else if (key == MINUS && (fdf->projection == ISOMETRIC ||
		fdf->projection == PARALLEL))
		(fdf->scale) > 5 && (fdf->scale -= 5);
	else if (key == MINUS && fdf->projection == PERSPECTIVE)
		fdf->camera.fov > 50 ? fdf->camera.fov -= 5 : 0;
	else if (key == C_KEY)
		if (++g_color > MAX_COLORS - 1)
			g_color = 0;
	if (key == PLUS || key == MINUS || key == C_KEY)
		return (1);
	return (0);
}

int8_t		shift_keys(int key, t_fdf *fdf)
{
	if (key == LEFT_ARROW)
		fdf->shift_x -= SHIFT_STEP;
	else if (key == RIGHT_ARROW)
		fdf->shift_x += SHIFT_STEP;
	else if (key == UP_ARROW)
		fdf->shift_y -= SHIFT_STEP;
	else if (key == DOWN_ARROW)
		fdf->shift_y += SHIFT_STEP;
	if (key == LEFT_ARROW || key == RIGHT_ARROW || key == DOWN_ARROW ||
		key == UP_ARROW)
		return (1);
	return (0);
}

void		copy_map(t_fdf *fdf)
{
	int32_t			i;
	int32_t			j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->trans_map[i][j].x = fdf->map[i][j].x;
			fdf->trans_map[i][j].y = fdf->map[i][j].y;
			fdf->trans_map[i][j].z = fdf->map[i][j].z;
			fdf->trans_map[i][j].w = fdf->map[i][j].w;
		}
	}
}
