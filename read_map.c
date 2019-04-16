/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:04:33 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/10 12:47:14 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_map(t_fdf *fdf, t_point_3d **map, t_list *file)
{
	char	**points;
	int32_t	x_amount;

	if (file->next)
		fill_map(fdf, map - 1, file->next);
	points = ft_strsplit((char *)(file->content), ' ', 0);
	x_amount = 0;
	while (points[x_amount])
		++x_amount;
	if (fdf->map_width != 0 && x_amount != fdf->map_width)
		ERROR_EXIT("Wrong map");
	fdf->map_width = x_amount;
	*map = (t_point_3d *)malloc(sizeof(t_point_3d) * x_amount);
	x_amount = 0;
	while (points[x_amount])
	{
		if (!ft_isdigit(points[x_amount][0]) && points[x_amount][0] != '-')
			ERROR_EXIT("Wrong map");
		(*map)[x_amount].z = ft_atoi(points[x_amount]);
		free(points[x_amount]);
		++x_amount;
	}
	free(points);
}

void		init_points_map(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;

	i = -1;
	fdf->trans_map = (t_point_3d **)malloc(sizeof(t_point_3d *) *
	fdf->map_height);
	while (++i < fdf->map_height)
	{
		j = -1;
		fdf->trans_map[i] = (t_point_3d *)malloc(sizeof(t_point_3d) *
		fdf->map_width);
	}
}

void		init_camera(t_fdf *fdf)
{
	fdf->camera.near = 10.0;
	fdf->camera.far = 45.0;
	fdf->camera.fov = 90;
	fdf->camera.aspect_ratio = ((double)WIN_HEIGHT / (double)WIN_WIDTH);
}

void		init_fdf(t_fdf *fdf)
{
	int32_t			i;
	int32_t			j;

	fdf->scale = 20;
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	fdf->x_rotate = 0;
	fdf->y_rotate = 0;
	fdf->z_rotate = 0;
	fdf->projections[0] = isometric_proj;
	fdf->projections[1] = parallel_proj;
	fdf->projections[2] = perspective_proj;
	init_camera(fdf);
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			fdf->map[i][j].w = 1.0;
		}
	}
	copy_map(fdf);
}

void		read_map(char *file_name, t_fdf *fdf)
{
	int32_t				fd;
	static t_list		*file = NULL;
	static t_list		*tmp = NULL;
	char				*line;

	ft_memset(fdf, 0, sizeof(*fdf));
	fd = open(file_name, O_RDONLY);
	if (errno)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit(1);
	}
	while (get_next_line(fd, &line, BUFF_SIZE) > 0)
	{
		tmp = ft_lstnew(line, ft_strlen(line) + 1);
		ft_lstadd(&file, tmp);
		free(line);
	}
	fdf->map_height = ft_lstsize(file);
	fdf->map = (t_point_3d **)malloc(sizeof(t_point_3d *) * fdf->map_height);
	fill_map(fdf, fdf->map + fdf->map_height - 1, file);
	init_points_map(fdf);
	init_fdf(fdf);
	clear_list(file);
	close(fd);
}
