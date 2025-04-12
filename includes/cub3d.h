/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:27:12 by soel-mou          #+#    #+#             */
/*   Updated: 2025/04/12 15:26:34 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

// Colors (merged from colors.h)
# define RESET "\e[0m"
# define RED "\e[31m"
# define YELLOW "\e[33m"
# define BRIGHT_RED "\e[91m"
# define BRIGHT_YELLOW "\e[93m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef DEBUG_MSG
#  define DEBUG_MSG 0
# endif

# ifndef MMAP_DEBUG_MSG
#  define MMAP_DEBUG_MSG 0
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.0125
# define ROTSPEED 0.015

# define DIST_EDGE_MOUSE_WRAP 20

# define MMAP_PIXEL_SIZE 128
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

enum					e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum					e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

// Simple struct for coordinates
typedef struct s_coords
{
	int		x;
	int		y;
}						t_coords;

typedef struct s_img
{
	void				*img;
	int					*addr;
	int					pixel_bits;
	int					size_line;
	int					endian;
}						t_img;

typedef struct s_texinfo
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	int					*floor;
	int					*ceiling;
	unsigned long		hex_floor;
	unsigned long		hex_ceiling;
	int					size;
	int					index;
	double				step;
	double				pos;
	int					x;
	int					y;
}						t_texinfo;

typedef struct s_mapinfo
{
	int					fd;
	int					line_count;
	char				*path;
	char				**file;
	int					height;
	int					width;
	int					index_end_of_map;
}						t_mapinfo;

typedef struct s_ray
{
	double				camera_x;
	double				dir_x;
	double				dir_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	double				sidedist_x;
	double				sidedist_y;
	double				deltadist_x;
	double				deltadist_y;
	double				wall_dist;
	double				wall_x;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_ray;

typedef struct s_player
{
	char				dir;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	int					has_moved;
	int					move_x;
	int					move_y;
	int					rotate;
}						t_player;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_height;
	int					win_width;
	t_mapinfo			mapinfo;
	char				**map;
	t_player			player;
	t_ray				ray;
	int					**texture_pixels;
	int					**textures;
	t_texinfo			texinfo;
	t_img				minimap;
}						t_data;

// Prototypes for included libft functions
int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_isspace(int c);
void					*ft_memset(void *b, int c, size_t len);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
size_t					ft_strlen(const char *s);
char					*get_next_line(int fd);
char					*f_strchr(char *s, int c);
char					*f_strdup(char *s1);
char					*f_strjoin(char *s1, char *s2);

void					init_data(t_data *data);
void					init_img_clean(t_img *img);
void					init_ray(t_ray *ray);

void					init_mlx(t_data *data);
void					init_img(t_data *data, t_img *image, int width,
							int height);
void					init_texture_img(t_data *data, t_img *image,
							char *path);

void					init_textures(t_data *data);
void					init_texinfo(t_texinfo *textures);

int						check_file(char *arg, bool cub);

void					parse_data(char *path, t_data *data);

int						get_file_data(t_data *data, char **map);

int						fill_color_textures(t_data *data, t_texinfo *textures,
							char *line, int j);

int						create_map(t_data *data, char **map, int i);

int						check_textures_validity(t_data *data,
							t_texinfo *textures);

int						check_map_validity(t_data *data, char **map_tab);

int						check_map_sides(t_mapinfo *map, char **map_tab);

int						is_a_white_space(char c);
size_t					find_biggest_len(t_mapinfo *map, int i);

int						render(t_data *data);
void					render_images(t_data *data);

int						raycasting(t_player *player, t_data *data);

void					init_texture_pixels(t_data *data);
void					update_texture_pixels(t_data *data, t_texinfo *tex,
							t_ray *ray, int x);

void					set_image_pixel(t_img *image, int x, int y, int color);

void					render_minimap(t_data *data);

void					render_minimap_image(t_data *data, int tile_size);

void					listen_for_input(t_data *data);

void					init_player_direction(t_data *data);

int						validate_move(t_data *data, double new_x, double new_y);

int						move_player(t_data *data);

int						rotate_player(t_data *data, double rotdir);

void					clean_exit(t_data *data, int code);
int						quit_cub3d(t_data *data);

void					free_tab(void **tab);
int						free_data(t_data *data);

int						err_msg(char *detail, char *str, int code);
int						err_msg_val(int detail, char *str, int code);

void					debug_display_data(t_data *data);
void					debug_display_player(t_data *data);
void					debug_print_char_tab(char **tab);

#endif
