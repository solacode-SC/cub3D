/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:26:00 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/12 19:36:57 by soel-mou         ###   ########.fr       */
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
	pos = (t_coords){x, y};
	if (tile == '1')
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_WALL);
	else if (tile == '0' || ft_strchr("NSEW", tile))
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_FLOOR);
	else
		set_minimap_tile_pixels(data, tile_size, pos, MMAP_COLOR_SPACE);
}

static void	draw_marker_pixel(t_data *data, t_coords center, t_coords offset,
		int map_pixel_w)
{
	int	px;
	int	py;
	int	map_pixel_h;

	map_pixel_h = data->mapinfo.height * (center.x / data->player.pos_x);
	px = center.x + offset.x;
	py = center.y + offset.y;
	if (px >= 0 && px < map_pixel_w && py >= 0 && py < map_pixel_h)
		set_image_pixel(&data->minimap, px, py, MMAP_COLOR_PLAYER);
}

static void	draw_player_on_minimap(t_data *data, int tile_size)
{
	t_coords	center;
	t_coords	offset;
	int			player_marker_size;
	int			map_pixel_w;

	center.x = (int)(data->player.pos_x * tile_size);
	center.y = (int)(data->player.pos_y * tile_size);
	player_marker_size = tile_size / 2;
	if (player_marker_size < 2)
		player_marker_size = 2;
	map_pixel_w = data->mapinfo.width * tile_size;
	offset.y = -player_marker_size / 2;
	while (offset.y <= player_marker_size / 2)
	{
		offset.x = -player_marker_size / 2;
		while (offset.x <= player_marker_size / 2)
		{
			draw_marker_pixel(data, center, offset, map_pixel_w);
			offset.x++;
		}
		offset.y++;
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
