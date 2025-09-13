/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:51:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/13 15:43:37 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERO_USA "Error\nusage: ./cub3d <file.cub>"
# define ERO_NAME_FILE "Error\nunsupported file"
# define ERO_OPEN_FILE "Error\nfailed to open file"
# define ERO_MAP "Error\nmap is invalid"
# define ERO_MALLOC "Error\nmalloc failed"
# define ERO_CLOSED_MAP "Error\n❌ Map is NOT closed!\n"
# define ERO_FILE "Error\nThe file is not accessible or doesn't exist"
# define ERO_READ "Error\nread failed"
# define ERO_CLOSE "Error\nclose failed"
# define ERO_MLX "Error\nmlx failed"
# define ERO_MLX_WIN "Error\nmlx_new_window failed"
# define ERO_MLX_IMG "Error\nmlx_new_image failed"
# define ERO_MLX_ADDR "Error\nmlx_get_data_addr failed"
# define ERO_MLX_INIT "Error\nmlx_init failed"

typedef struct s_map	t_map;
typedef struct s_row	t_row;
typedef struct s_cub3d	t_cub3d;
typedef struct s_player	t_player;
typedef struct s_point	t_point;
typedef struct s_color	t_color;

struct					s_player
{
	int					map_x;
	int					map_y;
};

struct					s_point
{
	int					x;
	int					y;
	int					access;
	int					width;
	int					height;
};

struct					s_row
{
	int					width;
	int					hight;
};

struct					s_color
{
	int					r;
	int					g;
	int					b;
};

struct					s_map
{
	int					map_width;
	int					map_height;
	int					**visited;
	char				**data;
	char				*file_path;
	char				*texture_north;
	char				*texture_south;
	char				*texture_west;
	char				*texture_east;
	char				*texture_sprite;
	t_color				color_floor;
	t_color				color_ceiling;
};

struct					s_cub3d
{
	int					is_empty;
	int					fd;
	int					flag;
	char				spawn;
	char				*file_path;
	t_map				map;
	t_player			player;
	t_row				*row_width;
	t_row				*colunm_height;
	t_point				**point;
};

# define WIN_W 1200
# define WIN_H 600

# define MINI_PAD 12
# define MINI_MAX_W 260
# define MINI_MAX_H 260
# define MINI_BG_A 0.45
# define MINI_CELL_A 0.70
# define MINI_DOT_SZ 4
# define MINI_HEADLEN 14

# define MINI_RAY_STEP 6
# define MINI_RAY_COL 0xFF0000

typedef struct s_line
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					dx;
	int					dy;
	int					steps;
	float				x_inc;
	float				y_inc;
	float				x;
	float				y;
}						t_line;

typedef struct s_pti
{
	int					x;
	int					y;
}						t_pti;

typedef struct s_sizei
{
	int					w;
	int					h;
}						t_sizei;

typedef struct s_clip
{
	int					x;
	int					y;
	int					w;
	int					h;
}						t_clip;

typedef struct s_blend
{
	unsigned int		color;
	double				alpha;
}						t_blend;

typedef struct s_lineopt
{
	t_clip				clip;
	unsigned int		color;
}						t_lineopt;

/* ── texture / runtime data ──────────────────────────────────────────────── */
typedef struct s_tex
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_tex;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;

	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;

	int					act_fwd;
	int					act_back;
	int					act_left;
	int					act_right;
	int					act_turn_l;
	int					act_turn_r;
	int					look_up;
	int					look_down;
	int					pitch;

	t_cub3d				*c3d;
	int					map_w;
	int					map_h;

	int					win_w;
	int					win_h;

	int					mm_x;
	int					mm_y;
	int					mm_w;
	int					mm_h;
	int					mm_scale;

	t_tex				tex[4];
	double				*hit_x;
	double				*hit_y;

	char				spawn;
}						t_data;

typedef struct s_cast
{
	double				cam_x;
	double				rx;
	double				ry;
	int					map_x;
	int					map_y;
	double				dx;
	double				dy;
	int					step_x;
	int					step_y;
	double				sx;
	double				sy;
	int					side;
	double				perp;
}						t_cast;

typedef struct s_slice
{
	int					h;
	int					draw_start;
	int					draw_end;
	int					tex_x;
	double				step;
	double				tex_pos;
	t_tex				*tex;
}						t_slice;

/* ── map parsing ─────────────────────────────────────────────────────────── */
int						is_spawn_char(char c);
int						handle_spawn_char(t_cub3d **cub3d, char c, int i);
int						check_map_values_condtion(t_cub3d **cub3d, char *line,
							int *check_empty);
void					set_map_values(t_cub3d **cub3d, char *line, int y);
int						check_map_values(t_cub3d **cub3d, char *line, int y);
void					fill_line_points(t_cub3d **cub3d, char *line, int y,
							int size);
void					fill_padding_points(t_cub3d **cub3d, int y, int start);
int						alloc_and_fill_points(t_cub3d **cub3d, char *line,
							int y);
void					apply_spawn_orientation(t_data *d);
void					set_plane(t_data *d, double px, double py);
void					set_dir(t_data *d, double dx, double dy);
void					free_map_points(t_cub3d *cub3d);
int						handle_locked_map(t_cub3d **cub3d, char *map_line,
							int *y);
int						handle_unlocked_map(char *map_line, int *lock);
int						check_map_condtion(t_cub3d **cub3d, char *map_line,
							int *lock, int *y);
char					*valid_set_texture_data(char *line, char *prefix);
void					set_texture_data(char *line, int skip, t_cub3d **cub3d);
void					set_color_data(int value, t_cub3d **cub3d, int which);
int						flood_fill(t_map *map, int x, int y, t_cub3d *cub3d);
int						setup_flood_fill(t_cub3d *cub3d);
int						ft_isspace(char c);
int						check_access(char *line);
int						open_file(t_cub3d **cub3d);
int						is_acceptable_file(char *line, int skip,
							t_cub3d **cub3d);
int						parsing_manager(t_cub3d **cub3d);
int						open_file_manager(t_cub3d **cub3d);
int						check_map_searching_2(t_cub3d **cub3d, char *map_line,
							int *lock, int *y);
int						comma_handle_color(char *line);
int						find_std_color_formial(char *line, int *lock,
							int *index);
int						handle_color_formality(char *line);
int						check_values(char *line, t_cub3d **cub3d, int which);
int						handle_color_data(char *line, int skip,
							t_cub3d **cub3d);
int						check_data_condition_2(char *trimmed_line,
							t_cub3d **cub3d, int *is_complete, int *height);
int						check_data_condition(char *trimmed_line,
							t_cub3d **cub3d, int *is_complete);
int						setup_check_data(char *line, t_cub3d **cub3d,
							int *is_complete);
int						setup_check_map(t_cub3d **cub3d, char **map_line);
int						check_map_searching(t_cub3d **cub3d, char *map_line,
							int *lock, int *y);
int						check_map(t_cub3d **cub3d);
int						handle_read_file(t_cub3d **cub3d, int *is_complete);
int						read_file(t_cub3d **cub3d);
int						map_status(t_cub3d **cub3d);
int						read_file_handle(t_cub3d **cub3d, char *line);
void					handle_get_next_line(int fd, char *line);
void					check_name(t_cub3d *cub3d);
void					free_texture(t_cub3d *cub3d);
void					init_cub3d(t_cub3d *cub3d, char *arg);
void					handle_error(char *error);
void					check_data_error(t_cub3d **cub3d, char *message,
							int flag);

/* ── pixels / primitives ─────────────────────────────────────────────────── */
void					put_pixel(t_data *d, int x, int y, unsigned int color);
unsigned int			get_pixel(t_data *d, int x, int y);
unsigned int			tex_get_pixel(t_tex *t, int x, int y);
unsigned int			blend_rgb(unsigned int dst, unsigned int src, double a);
void					put_pixel_blend(t_data *d, int xy[], unsigned int color,
							double a);
int						cleanup_and_exit(t_data *d, t_cub3d *c3d, int code);
void					draw_line(t_data *d, int x01, int y01[],
							unsigned int c);
void					check_data_draw_line(int dsxy[], int *err);
void					draw_rect_blend(t_data *d, int xywh[], unsigned int c,
							double a);
void					draw_rect(t_data *d, int xywh[], unsigned int c);
void					draw_line_clip(t_data *d, int xy01[], unsigned int c);

/* ── controls / movement ─────────────────────────────────────────────────── */
int						key_press(int kc, t_data *d);
int						key_release(int kc, t_data *d);
int						close_game(t_data *d);
int						is_key_w(int kc);
int						is_key_s(int kc);
int						is_key_a(int kc);
int						is_key_d(int kc);
int						is_key_left(int kc);
int						is_key_right(int kc);
int						is_key_up(int kc);
int						is_key_down(int kc);
int						is_key_esc(int kc);
int						is_key_r(int kc);
int						is_key_f(int kc);
void					move_fwd_back(t_data *d, double ms);
void					move_strafe(t_data *d, double ms);
void					rotate_dir_plane(t_data *d, double rs);
void					update_pitch(t_data *d, double dt);
void					move_player(t_data *d, double dt);

/* ── sky / floor ─────────────────────────────────────────────────────────── */
void					draw_sky_floor(t_data *d);

/* ── raycast ─────────────────────────────────────────────────────────────── */
void					cast_init(t_data *d, t_cast *c, int col);
void					cast_init_ray(t_data *d, t_cast *c, int col);
void					cast_init_dda(t_data *d, t_cast *c);
void					cast_step_to_hit_check(t_data *d, t_cast *c, int *hit);
void					cast_step_to_hit(t_data *d, t_cast *c);
void					draw_slice_store_hit(t_data *d, t_cast *c, int col);
void					cast_and_draw_column(t_data *d, int col);

/* ── textures lifecycle ──────────────────────────────────────────────────── */
int						init_textures(t_data *d);
void					destroy_textures(t_data *d);

/* ── frame ───────────────────────────────────────────────────────────────── */
int						render_frame(void *param);

/* ── init / alloc ────────────────────────────────────────────────────────── */
void					init_player_camera(t_data *d);
int						init_gfx(t_data *d);
int						alloc_ray_buffers(t_data *d);
#endif
