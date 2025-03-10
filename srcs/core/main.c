
#include "../../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        printf("Error\nUsage: ./cub3D <map.cub>\n");
        return (1);
    }
    
    // Initialize game with zeroed memory
    ft_memset(&game, 0, sizeof(t_game));
    game.win_width = SCREEN_WIDTH;
    game.win_height = SCREEN_HEIGHT;
    game.is_running = 1;
    
    // Initialize game and MLX
    if (!init_game(&game, argv[1]))
        return (1);
    
    // Set up hooks
    mlx_hook(game.mlx.win_ptr, 2, 1L<<0, key_press, &game);
    mlx_hook(game.mlx.win_ptr, 3, 1L<<1, key_release, &game);
    mlx_hook(game.mlx.win_ptr, 17, 0, close_window, &game);
    
    // Start game loop
    mlx_loop_hook(game.mlx.mlx_ptr, render_frame, &game);

    mlx_loop(game.mlx.mlx_ptr);
    
    // Clean up (this won't be reached normally, but good practice)
    cleanup_game(&game);
    return (0);
}