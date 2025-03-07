
#include "../../includes/cub3d.h"

// Initialize MiniLibX and create window
static int init_mlx(t_game *game)
{
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
        return (0);
    
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, 
        game->win_width, game->win_height, TITLE);
    if (!game->mlx.win_ptr)
        return (0);
    
    game->mlx.img = mlx_new_image(game->mlx.mlx_ptr, 
        game->win_width, game->win_height);
    if (!game->mlx.img)
        return (0);
    
    game->mlx.addr = (int *)mlx_get_data_addr(game->mlx.img, 
        &game->mlx.bits_per_pixel, &game->mlx.line_length, &game->mlx.endian);
    
    return (1);
}

// Initialize player based on map data
void init_player(t_game *game)
{
    // Set player position
    game->player.pos.x = game->map.player_pos.x + 0.5;
    game->player.pos.y = game->map.player_pos.y + 0.5;
    
    // Set initial direction based on map
    if (game->map.player_dir == 'N')
    {
        game->player.dir.x = 0;
        game->player.dir.y = -1;
        game->player.plane.x = 0.66;
        game->player.plane.y = 0;
    }
    else if (game->map.player_dir == 'S')
    {
        game->player.dir.x = 0;
        game->player.dir.y = 1;
        game->player.plane.x = -0.66;
        game->player.plane.y = 0;
    }
    else if (game->map.player_dir == 'E')
    {
        game->player.dir.x = 1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = 0.66;
    }
    else if (game->map.player_dir == 'W')
    {
        game->player.dir.x = -1;
        game->player.dir.y = 0;
        game->player.plane.x = 0;
        game->player.plane.y = -0.66;
    }
    
    // Set movement speeds
    game->player.move_speed = 0.05;
    game->player.rot_speed = 0.03;
}

// Main initialization function
int init_game(t_game *game, char *map_path)
{
    // Initialize MLX
    if (!init_mlx(game))
    {
        printf("Error\nFailed to initialize MLX\n");
        return (0);
    }
    
    // Parse map (basic temporary implementation)
    if (!parse_map(game, map_path))
        return (0);
    
    // Initialize player
    init_player(game);
    
    return (1);
}