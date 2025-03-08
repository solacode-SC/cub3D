
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
#include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define TITLE "cub3D"

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

/* Vector structure for 2D coordinates and directions */
typedef struct s_vec2
{
    double x;
    double y;
} t_vec2;

/* RGB color structure */
typedef struct s_color
{
    int r;
    int g;
    int b;
    int value;
} t_color;

/* Texture structure */
typedef struct s_texture
{
    void    *img;
    char    *path;
    int     *data;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_texture;

/* Player structure */
typedef struct s_player
{
    t_vec2  pos;
    t_vec2  dir;
    t_vec2  plane;
    double  move_speed;
    double  rot_speed;
} t_player;

/* Map structure */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    player_dir;
    t_vec2  player_pos;
} t_map;

/* Configuration from .cub file */
typedef struct s_config
{
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    t_color floor;
    t_color ceiling;
} t_config;

/* MiniLibX graphics context */
typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img;
    int     *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_mlx;

/* Key states for smooth movement */
typedef struct s_keys
{
    int     w;
    int     s;
    int     a;
    int     d;
    int     left;
    int     right;
} t_keys;

/* Main game structure */
typedef struct s_game
{
    t_mlx       mlx;
    t_config    config;
    t_map       map;
    t_player    player;
    t_texture   textures[4];
    t_keys      keys;
    
    int         win_width;
    int         win_height;
    int         is_running;
} t_game;

/* init.c */
int     init_game(t_game *game, char *map_path);
void    init_player(t_game *game);

/* parser.c */
int     parse_map(t_game *game, char *map_path);

/* input.c */
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);
int     close_window(t_game *game);

/* render.c */
void    render_frame(t_game *game);

/* cleanup.c */
void    cleanup_game(t_game *game);
void    error_exit(t_game *game, char *message);

/*utils functions */
void	*ft_memset(void *b, int c, size_t len);

#endif