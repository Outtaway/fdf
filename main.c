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

int					exit_function(void *param)
{
	(void)param;
	system("leaks fdf");
	exit(0);
	return (0);
}

int					key_handler(int key, void *param)
{
	t_fdf				*fdf;

	fdf = (t_fdf *)param;
	copy_map(fdf);
	ft_memset(fdf->img_data, 0, WIN_HEIGHT * WIN_WIDTH * (fdf->bpp / 8));
	if (key == R_KEY)
		init_fdf(fdf);
	else if (key == ESC)
		exit_function(NULL);
	else if (key == P_KEY)
		fdf->projection += fdf->projection == 2 ? -2 : 1;
	else if (rotations_keys(key, fdf))
		;
	else if (scale_or_colors_keys(key, fdf))
		;
	else if (shift_keys(key, fdf))
		;
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
	(fdf->projections[fdf->projection])(fdf);
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
