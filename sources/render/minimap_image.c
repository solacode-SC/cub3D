/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:26:00 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/11 22:26:01 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_minimap_tile_pixels(t_data *data, int tile_size, int map_x, int map_y, int color)
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
			pixel_x = map_x * tile_size + j;
			pixel_y = map_y * tile_size + i;
			if (pixel_x < data->mapinfo.width * tile_size && pixel_y < data->mapinfo.height * tile_size)
				set_image_pixel(&data->minimap, pixel_x, pixel_y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_data *data, int tile_size, int x, int y)
{
	char	tile = data->map[y][x];

	if (tile == '1')
		set_minimap_tile_pixels(data, tile_size, x, y, MMAP_COLOR_WALL);
	else if (tile == '0' || ft_strchr("NSEW", tile)) // Treat player start pos as floor
		set_minimap_tile_pixels(data, tile_size, x, y, MMAP_COLOR_FLOOR);
	else // Empty space or characters outside map
		set_minimap_tile_pixels(data, tile_size, x, y, MMAP_COLOR_SPACE);
}

static void	draw_player_on_minimap(t_data *data, int tile_size)
{
	int	player_pixel_x;
	int	player_pixel_y;
	int	player_marker_size;
	int	i;
	int	j;

	// Calculate player pixel position
	player_pixel_x = (int)(data->player.pos_x * tile_size);
	player_pixel_y = (int)(data->player.pos_y * tile_size);

	// Simple square marker for the player
	player_marker_size = tile_size / 2; // Make marker smaller than tile
	if (player_marker_size < 2)
		player_marker_size = 2; // Minimum marker size

	i = -player_marker_size / 2;
	while (i <= player_marker_size / 2)
	{
		j = -player_marker_size / 2;
		while (j <= player_marker_size / 2)
		{
			if (player_pixel_x + j >= 0 && player_pixel_x + j < data->mapinfo.width * tile_size
				&& player_pixel_y + i >= 0 && player_pixel_y + i < data->mapinfo.height * tile_size)
				set_image_pixel(&data->minimap, player_pixel_x + j, player_pixel_y + i, MMAP_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_minimap(t_data *data, int tile_size)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mapinfo.height)
	{
		x = 0;
		while (x < data->mapinfo.width)
		{
			if (data->map[y] && x < (int)ft_strlen(data->map[y]))
				draw_minimap_tile(data, tile_size, x, y);
			else
				set_minimap_tile_pixels(data, tile_size, x, y, MMAP_COLOR_SPACE); // Draw empty space if outside map bounds
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
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img,
		5, data->win_height - img_height - 5); // Position in bottom-left corner with padding
	mlx_destroy_image(data->mlx, data->minimap.img);
}
