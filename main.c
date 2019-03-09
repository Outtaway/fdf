/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:20:35 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/09 20:09:10 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point_2d start, t_point_2d end, t_fdf *fdf)
{
	const int deltaX = abs(end.x - start.x);
	const int deltaY = abs(end.y - start.y);
	const int signX = start.x < end.x ? 1 : -1;
	const int signY = start.y < end.y ? 1 : -1;
	int error = deltaX - deltaY;

	while(start.x != end.x || start.y != end.y) 
	{
		mlx_pixel_put(fdf->mlx, fdf->win, start.x, start.y, GREEN);
		const int error2 = error * 2;
		if(error2 > -deltaY) 
		{
			error -= deltaY;
			start.x += signX;
		}
		if(error2 < deltaX) 
		{
			error += deltaX;
			start.y += signY;
		}
	}
}

void	draw_map(t_fdf *fdf)
{
	int32_t			i;
	int32_t			j;

	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width - 1)
		{
			draw_line(_2DPOINT(fdf->projected_map[i][j].x, fdf->projected_map[i][j].y),
				_2DPOINT(fdf->projected_map[i][j + 1].x, fdf->projected_map[i][j + 1].y), fdf);
		}
	}
	i = -1;
	while (++i < fdf->map_width)
	{
		j = -1;
		while (++j < fdf->map_height - 1)
		{
			draw_line(_2DPOINT(fdf->projected_map[j][i].x, fdf->projected_map[j][i].y),
				_2DPOINT(fdf->projected_map[j + 1][i].x, fdf->projected_map[j + 1][i].y), fdf);
		}
	}
}

int8_t	isometric_proj(t_fdf *fdf, int32_t angle)
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
			prev_x = fdf->transformed_map[i][j].x;
			prev_y = fdf->transformed_map[i][j].y;
			fdf->projected_map[i][j].x = (prev_x - prev_y) * cos(TO_RAD(angle)) + fdf->shift_x + (prev_x * fdf->scale);
			fdf->projected_map[i][j].y = (prev_x + prev_y) * sin(TO_RAD(angle)) - fdf->transformed_map[i][j].z + fdf->shift_y + (prev_y * fdf->scale);
		}
	}
	return (1);
}

int		exit_func(int key, void *param)
{
	int8_t		redraw;

	redraw = 0;
	copy_map((t_fdf *)param);
	if (key == 53)
		exit(EXIT_SUCCESS);
	else if (key == 86)
		(redraw = 1) && ((((t_fdf *)param)->x_rotate) += 10);
	else if (key == 88)
		(redraw = 1) && ((((t_fdf *)param)->x_rotate) -= 10);
	else if (key == 91)
		(redraw = 1) && ((((t_fdf *)param)->y_rotate) += 10);
	else if (key == 84)
		(redraw = 1) && ((((t_fdf *)param)->y_rotate) -= 10);
	else if (key == 123)
		(redraw = 1) && ((((t_fdf *)param)->shift_x) -= 5);
	else if (key == 124)
		(redraw = 1) && ((((t_fdf *)param)->shift_x) += 5);
	else if (key == 126)
		(redraw = 1) && ((((t_fdf *)param)->shift_y) -= 5);
	else if (key == 125)
		(redraw = 1) && ((((t_fdf *)param)->shift_y) += 5);
	else if (key == 24)
		(redraw = 1) && ((((t_fdf *)param)->scale) += 5);
	else if (key == 27)
		((((t_fdf *)param)->scale) > 5) && (redraw = 1) && ((((t_fdf *)param)->scale) -= 5);
	else if (key == 6)
		((t_fdf *)param)->z_modif += 5;
	else if (key == 7)
		((t_fdf *)param)->z_modif -= 5;	
	if (redraw)
	{
		rotate_x((t_fdf *)param);
		rotate_y((t_fdf *)param);
		rotate_z((t_fdf *)param);
		isometric_proj((t_fdf *)param, 0);
		mlx_clear_window(((t_fdf *)param)->mlx, ((t_fdf *)param)->win);
		draw_map((t_fdf *)param);
	}
	return (EXIT_SUCCESS);
}


int		main(int ac, char **av)
{
	t_fdf		fdf;

	if (ac != 2)
	{
		write(2, "Usage: ./fdf [filename]\n", 25);
		exit(EXIT_FAILURE);
	}
	read_map(av[1], &fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "FDF");
	mlx_key_hook(fdf.win, exit_func, &fdf);
	isometric_proj(&fdf, 0);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	mlx_destroy_window(fdf.mlx, fdf.win);
	return (0);
}
