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
	{
		write(2, "Wrong map!", 10);
		exit(EXIT_FAILURE);
	}
	fdf->map_width = x_amount;
	*map = (t_point_3d *)malloc(sizeof(t_point_3d) * x_amount);
	x_amount = 0;
	while (points[x_amount])
	{
		if (!ft_isdigit(points[x_amount][0]) && points[x_amount][0] != '-')
		{
			write(2, "Wrong map!", 10);
			exit(EXIT_FAILURE);
		}
		(*map)[x_amount].z = ft_atoi(points[x_amount]);
		free(points[x_amount]);
		++x_amount;
	}
	free(points);
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

void		init_fdf(t_fdf *fdf)
{
	int32_t		i;
	int32_t		j;

	i = -1;
	fdf->scale = 30;
	fdf->trans_map = (t_point_3d **)malloc(sizeof(t_point_3d *) * fdf->map_height);
	while (++i < fdf->map_height)
	{
		j = -1;
		fdf->trans_map[i] = (t_point_3d *)malloc(sizeof(t_point_3d) * fdf->map_width);
		while (++j < fdf->map_width)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			fdf->map[i][j].w = 1.0;
			fdf->trans_map[i][j].x = fdf->map[i][j].x;
			fdf->trans_map[i][j].y = fdf->map[i][j].y;
			fdf->trans_map[i][j].z = fdf->map[i][j].z;
			fdf->trans_map[i][j].w = fdf->map[i][j].w;
		}
	}
	fdf->shift_x = WIN_WIDTH / 2;
	fdf->shift_y = WIN_HEIGHT / 2;
	fdf->projection = ISOMETRIC;
}

void		clear_list(t_list *list)
{
	if (list)
	{
		if (list->next)
			clear_list(list->next);
		free(list->content);
		free(list);
	}
}

void		read_map(char *file_name, t_fdf *fdf)
{
	int32_t		fd;
	t_list		*file;
	t_list		*tmp;
	char		*line;

	ft_memset(fdf, 0, sizeof(*fdf));
	fd = open(file_name, O_RDONLY);
	if (errno)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit(1);
	}
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
	fdf->camera.near = 15.0;
	fdf->camera.far = 40.0;
	fdf->camera.fov = 90;
	fdf->projection = ISOMETRIC;
	fdf->camera.aspect_ratio = ((double)WIN_HEIGHT / (double)WIN_WIDTH);
	fill_map(fdf, fdf->map + fdf->map_height - 1, file);
	init_fdf(fdf);
	clear_list(file);
	close(fd);
}