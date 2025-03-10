
#include "../../includes/cub3d.h"

// Put a pixel to the image
static void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
        mlx->addr[y * (mlx->line_length / 4) + x] = color;
}

// Fill the screen with a basic color for now
static void fill_screen(t_game *game)
{
    int x;
    int y;
    int color;

    y = 0;
    while (y < game->win_height)
    {
        x = 0;
        while (x < game->win_width)
        {
            // Draw ceiling in the top half
            if (y < game->win_height / 2)
                color = 0x87CEEB; // Sky blue
            // Draw floor in the bottom half
            else
                color = 0x8B4513; // Brown
            
            my_mlx_pixel_put(&game->mlx, x, y, color);
            x++;
        }
        y++;
    }
}

// Render a frame
int render_frame(void *param)
{
    t_game *game = (t_game *)param; // Cast param to t_game*

    if (!game->is_running)
        return (0);

    // Fill the screen with basic colors
    fill_screen(game);

    // TODO: Implement raycasting here

    // Put the image to the window
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->mlx.img, 0, 0);

    return (0);
}
