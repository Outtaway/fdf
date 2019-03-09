/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:04:33 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/10 00:14:51 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_map(t_fdf *fdf, t_point_3d **map, t_list *file)
{
	// free points
	char	**points;
	int32_t	x_amount;

	if (file->next)
		fill_map(fdf, map - 1, file->next);
	points = ft_strsplit((char *)(file->content), ' ', 0);
	x_amount = 0;
	while (points[x_amount])
		++x_amount;
	fdf->map_width = x_amount;
	*map = (t_point_3d *)malloc(sizeof(t_point_3d) * x_amount);
	x_amount = 0;
	while (points[x_amount])
	{
		(*map)[x_amount].z = ft_atoi(points[x_amount]);
		++x_amount;
	}
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
			fdf->transformed_map[i][j].x = fdf->map[i][j].x;
			fdf->transformed_map[i][j].y = fdf->map[i][j].y;
			fdf->transformed_map[i][j].z = fdf->map[i][j].z;
		}
	}
}

void		init_fdf(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;

	i = -1;
	fdf->scale = 30;
	fdf->x_rotate = 0;
	fdf->y_rotate = 0;
	fdf->z_rotate = 0;
	fdf->transformed_map = (t_point_3d **)malloc(sizeof(t_point_3d *) * fdf->map_height);
	fdf->projected_map = (t_point_2d **)malloc(sizeof(t_point_2d *) * fdf->map_height);
	while (++i < fdf->map_height)
	{
		j = -1;
		fdf->transformed_map[i] = (t_point_3d *)malloc(sizeof(t_point_3d) * fdf->map_width);
		fdf->projected_map[i] = (t_point_2d *)malloc(sizeof(t_point_2d) * fdf->map_width);
		while (++j < fdf->map_width)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			fdf->transformed_map[i][j].y = fdf->map[i][j].x;
			fdf->transformed_map[i][j].x = fdf->map[i][j].y;
			fdf->transformed_map[i][j].z = fdf->map[i][j].z;
		}
	}
	fdf->shift_x = 500;
	fdf->shift_y = 200;
	fdf->z_modif = 0;
}

void		read_map(char *file_name, t_fdf *fdf)
{
	int32_t		fd;
	t_list		*file;
	t_list		*tmp;
	char		*line;

	fd = open(file_name, O_RDONLY);
	file = NULL;
	tmp = NULL;
	while (get_next_line(fd, &line, BUFF_SIZE) > 0)
	{
		tmp = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&file, tmp);
		free(line);
	}
	fdf->map_height = ft_lstsize(file);
	fdf->map = (t_point_3d **)malloc(sizeof(t_point_3d *) * fdf->map_height);
	fill_map(fdf, fdf->map + fdf->map_height - 1, file);
	init_fdf(fdf);
	// rotate_x(fdf);
	// rotate_y(fdf);
	// rotate_z(fdf);
	// int i = 0;
	// while (i < fdf->map_height)
	// {
	// 	int j = 0;
	// 	while (j < fdf->map_width)
	// 	{
	// 		ft_printf("%3d", fdf->map[i][j].value);
	// 		++j;
	// 	}
	// 	ft_printf("\n");
	// 	++i;
	// }
}