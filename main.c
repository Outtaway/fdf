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

int32_t				g_colors[4] = { WHITE, RED, GREEN, BLUE };
int32_t				g_color = 0;

void				draw_line(t_point_2d start, t_point_2d end, t_fdf *fdf)
{
	const int	deltax = abs(end.x - start.x);
	const int	deltay = abs(end.y - start.y);
	const int	signx = start.x < end.x ? 1 : -1;
	const int	signy = start.y < end.y ? 1 : -1;
	int			error[2];

	error[0] = deltax - deltay;
	while (start.x != end.x || start.y != end.y)
	{
		if (start.x < WIN_WIDTH && start.x > 0 && start.y > 0 && start.y <
			WIN_HEIGHT)
			*((int*)(fdf->img_data + (start.y * WIN_WIDTH + start.x) *
			(fdf->bpp / 8))) = g_colors[g_color];
		error[1] = error[0] * 2;
		if (error[1] > -deltay)
		{
			error[0] -= deltay;
			start.x += signx;
		}
		if (error[1] < deltax)
		{
			error[0] += deltax;
			start.y += signy;
		}
	}
}

void				draw_map(t_fdf *fdf)
{
	int32_t			i;
	int32_t			j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width - 1)
		{
			draw_line(_2DPOINT(fdf->trans_map[i][j].x,
			fdf->trans_map[i][j].y), _2DPOINT(fdf->trans_map[i][j + 1].x,
				fdf->trans_map[i][j + 1].y), fdf);
		}
	}
	i = -1;
	while (++i < fdf->map_width)
	{
		j = -1;
		while (++j < fdf->map_height - 1)
		{
			draw_line(_2DPOINT(fdf->trans_map[j][i].x,
			fdf->trans_map[j][i].y), _2DPOINT(fdf->trans_map[j + 1][i].x,
				fdf->trans_map[j + 1][i].y), fdf);
		}
	}
}

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
			fdf->trans_map[i][j].x = (prev_x - prev_y) * cos(0.523599) +
			fdf->shift_x + (prev_x * fdf->scale);
			fdf->trans_map[i][j].y = (prev_x + prev_y) * sin(0.523599) -
			fdf->trans_map[i][j].z + fdf->shift_y + (prev_y * fdf->scale);
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

int					exit_function(void *param)
{
	system("leaks fdf");
	exit(0);
	return (0);
}

int					key_handler(int key, void *param)
{
	t_fdf				*fdf;

	fdf = (t_fdf *)param;
	copy_map(fdf);
	ft_memset(((t_fdf *)param)->img_data, 0,
		WIN_HEIGHT * WIN_WIDTH * (fdf->bpp / 8));
	if (key == ESC)
		exit_function(NULL);
	else if (key == P_KEY)
		fdf->projection = (fdf->projection == ISOMETRIC) ?
			PERSPECTIVE : ISOMETRIC;
	else if (key == NUM8)
		fdf->x_rotate += ROTATE_STEP;
	else if (key == NUM2)
		fdf->x_rotate -= ROTATE_STEP;
	else if (key == NUM6)
		fdf->y_rotate += ROTATE_STEP;
	else if (key == NUM4)
		fdf->y_rotate -= ROTATE_STEP;
	else if (key == LEFT_ARROW)
		fdf->shift_x -= SHIFT_STEP;
	else if (key == RIGHT_ARROW)
		fdf->shift_x += SHIFT_STEP;
	else if (key == UP_ARROW)
		fdf->shift_y -= SHIFT_STEP;
	else if (key == DOWN_ARROW)
		fdf->shift_y += SHIFT_STEP;
	else if (key == PLUS && fdf->projection == ISOMETRIC)
		fdf->scale += 5;
	else if (key == PLUS && fdf->projection == PERSPECTIVE)
		fdf->camera.fov < 110 ? fdf->camera.fov += 5 : 0;
	else if (key == MINUS && fdf->projection == ISOMETRIC)
		(fdf->scale) > 5 && (fdf->scale -= 5);
	else if (key == MINUS && fdf->projection == PERSPECTIVE)
		fdf->camera.fov > 50 ? fdf->camera.fov -= 5 : 0;
	else if (key == C_KEY)
		if (++g_color > MAX_COLORS - 1)
			g_color = 0;
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
	fdf->projection == ISOMETRIC ? isometric_proj(fdf) :
		perspective_proj(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (EXIT_SUCCESS);
}

int					main(int ac, char **av)
{
	t_fdf		fdf;

	errno = 0;
	if (ac != 2)
	{
		write(2, "Usage: ./fdf [filename]\n", 25);
		exit(EXIT_FAILURE);
	}
	read_map(av[1], &fdf);
	fdf.mlx = mlx_init();
	fdf.img = mlx_new_image(fdf.mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf.img_data = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.size_line,
			&fdf.endian);
	fdf.win = mlx_new_window(fdf.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	mlx_hook(fdf.win, 2, 5, key_handler, &fdf);
	mlx_hook(fdf.win, 17, 5, exit_function, &fdf);
	key_handler(-42, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
