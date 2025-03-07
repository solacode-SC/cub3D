
#include "../../includes/cub3d.h"

// Free the map data
static void free_map(t_map *map)
{
    int i;

    if (!map->grid)
        return;
    
    i = 0;
    while (i < map->height && map->grid[i])
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
    map->grid = NULL;
}

// Clean up textures
static void free_textures(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx.mlx_ptr, game->textures[i].img);
        if (game->textures[i].path)
            free(game->textures[i].path);
        i++;
    }
}

// Clean up configuration
static void free_config(t_config *config)
{
    if (config->no_path)
        free(config->no_path);
    if (config->so_path)
        free(config->so_path);
    if (config->we_path)
        free(config->we_path);
    if (config->ea_path)
        free(config->ea_path);
}

// Clean up everything
void cleanup_game(t_game *game)
{
    // Free map
    free_map(&game->map);
    
    // Free textures
    free_textures(game);
    
    // Free configuration
    free_config(&game->config);
    
    // Clean up MLX
    if (game->mlx.img)
        mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img);
    if (game->mlx.win_ptr)
        mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
    // Note: Some MLX implementations need to free mlx_ptr, others don't
}

// Error and exit
void error_exit(t_game *game, char *message)
{
    printf("Error\n%s\n", message);
    cleanup_game(game);
    exit(1);
}