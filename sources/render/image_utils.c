/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:25:57 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/12 19:38:22 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
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
