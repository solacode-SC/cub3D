/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:26:00 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/12 19:17:52 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_minimap_tile_pixels(t_data *data, int tile_size,
		t_coords map_pos, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			pixel_x = map_pos.x * tile_size + j;
			pixel_y = map_pos.y * tile_size + i;
			if (pixel_x >= 0 && pixel_x < data->minimap.size_line
				/ (data->minimap.pixel_bits / 8) && pixel_y >= 0
				&& pixel_y < data->mapinfo.height * tile_size)
				set_image_pixel(&data->minimap, pixel_x, pixel_y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_data *data, int tile_size, int x, int y)
{
	char		tile;
	t_coords	pos;

	tile = data->map[y][x];
	pos = {x, y};
	if (tile == '1')
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_WALL);
	else if (tile == '0' || ft_strchr("NSEW", tile))
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_FLOOR);
	else
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_SPACE);
}

static void	draw_player_on_minimap(t_data *data, int tile_size)
{
	int	player_pixel_x;
	int	player_pixel_y;
	int	player_marker_size;
	int	i;
	int	j;

	player_pixel_x = (int)(data->player.pos_x * tile_size);
	player_pixel_y = (int)(data->player.pos_y * tile_size);
	player_marker_size = tile_size / 2;
	if (player_marker_size < 2)
		player_marker_size = 2;
	i = -player_marker_size / 2;
	while (i <= player_marker_size / 2)
	{
		j = -player_marker_size / 2;
		while (j <= player_marker_size / 2)
		{
			if (player_pixel_x + j >= 0 && player_pixel_x
				+ j < data->mapinfo.width * tile_size && player_pixel_y + i >= 0
				&& player_pixel_y + i < data->mapinfo.height * tile_size)
				set_image_pixel(&data->minimap, player_pixel_x + j,
					player_pixel_y + i, MMAP_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_minimap(t_data *data, int tile_size)
{
	int			x;
	int			y;
	t_coords	pos;

	y = 0;
	while (y < data->mapinfo.height)
	{
		x = 0;
		while (x < data->mapinfo.width)
		{
			pos.x = x;
			pos.y = y;
			if (data->map[y] && x < (int)ft_strlen(data->map[y]))
				draw_minimap_tile(data, tile_size, x, y);
			else
				set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_SPACE);
			x++;
		}
		y++;
	}
	draw_player_on_minimap(data, tile_size);
}

void	render_minimap_image(t_data *data, int tile_size)
{
	int	img_width;
	int	img_height;

	img_width = data->mapinfo.width * tile_size;
	img_height = data->mapinfo.height * tile_size;
	init_img(data, &data->minimap, img_width, img_height);
	draw_minimap(data, tile_size);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 5,
		data->win_height - img_height - 5);
	mlx_destroy_image(data->mlx, data->minimap.img);
}
