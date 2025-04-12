/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:26:04 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/11 22:26:05 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(t_data *data)
{
	int		tile_size_x;
	int		tile_size_y;
	int		tile_size;

	// Calculate tile size to fit the map into MMAP_PIXEL_SIZE
	tile_size_x = MMAP_PIXEL_SIZE / data->mapinfo.width;
	tile_size_y = MMAP_PIXEL_SIZE / data->mapinfo.height;
	tile_size = tile_size_x;
	if (tile_size_y < tile_size_x)
		tile_size = tile_size_y;
	if (tile_size < 1)
		tile_size = 1; // Ensure tile size is at least 1 pixel

	render_minimap_image(data, tile_size);
}
