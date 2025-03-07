
#include "../../includes/cub3d.h"

// This is a very basic placeholder parser
// In a real implementation, you'd need to properly read the .cub file
int parse_map(t_game *game, char *map_path)
{
    (void)map_path; // Avoid unused parameter warning
    
    // Temporary hardcoded map for testing the window
    char *temp_map[] = {
        "111111",
        "100001",
        "100001",
        "1000N1",
        "100001",
        "111111",
        NULL
    };
    
    game->map.width = 6;
    game->map.height = 6;
    
    // Allocate memory for the map grid
    game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
    if (!game->map.grid)
        return (0);
    
    // Copy the temporary map
    for (int i = 0; i < game->map.height; i++)
    {
        game->map.grid[i] = strdup(temp_map[i]);
        if (!game->map.grid[i])
            return (0);
        
        // Find player position
        for (int j = 0; j < game->map.width; j++)
        {
            if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S' || 
                game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
            {
                game->map.player_dir = game->map.grid[i][j];
                game->map.player_pos.x = j;
                game->map.player_pos.y = i;
                // Replace with a 0 (empty space)
                game->map.grid[i][j] = '0';
            }
        }
    }
    game->map.grid[game->map.height] = NULL;
    
    // Temporary hardcoded colors
    game->config.floor.r = 100;
    game->config.floor.g = 100;
    game->config.floor.b = 100;
    game->config.floor.value = 0x646464;
    
    game->config.ceiling.r = 135;
    game->config.ceiling.g = 206;
    game->config.ceiling.b = 235;
    game->config.ceiling.value = 0x87CEEB;
    
    return (1);
}