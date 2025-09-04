/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/04 14:19:46 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OVERLAY_H
# define OVERLAY_H

# include "../includes/cub3d.h"

/* ── window / minimap config ─────────────────────────────────────────────── */

#define WIN_W          1200
#define WIN_H          600

#define MINI_PAD       12
#define MINI_MAX_W     260
#define MINI_MAX_H     260
#define MINI_BG_A      0.45
#define MINI_CELL_A    0.70
#define MINI_DOT_SZ    4
#define MINI_HEADLEN   14

#define MINI_RAY_STEP  6
#define MINI_RAY_COL   0xFF0000


/* ─── add after your other typedefs ─────────────────────────────────────── */
typedef struct s_pti
{
	int	x;
	int	y;
}	t_pti;

typedef struct s_sizei
{
	int	w;
	int	h;
}	t_sizei;

typedef struct s_clip
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_clip;

typedef struct s_blend
{
	unsigned int	color;
	double			alpha;
}	t_blend;

typedef struct s_lineopt
{
	t_clip			clip;
	unsigned int	color;
}	t_lineopt;
/* ───────────────────────────────────────────────────────────────────────── */

/* ─── replace old prototypes (many args) with these ─────────────────────── */
/* ───────────────────────────────────────────────────────────────────────── */

/* ── overlay data ────────────────────────────────────────────────────────── */

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	
	int			act_fwd;
	int			act_back;
	int			act_left;
	int			act_right;
	int			act_turn_l;
	int			act_turn_r;
	int			look_up;
	int			look_down;
	int			pitch;
	
	t_cub3d		*c3d;
	int			map_w;
	int			map_h;


	int			win_w;
	int			win_h;

	int			mm_x;
	int			mm_y;
	int			mm_w;
	int			mm_h;
	int			mm_scale;

	double		*hit_x;
	double		*hit_y;
}	t_data;

typedef struct s_cast
{
	double	cam_x;
	double	rx;
	double	ry;
	int		map_x;
	int		map_y;
	double	dx;
	double	dy;
	int		step_x;
	int		step_y;
	double	sx;
	double	sy;
	int		side;
	double	perp;
}	t_cast;


/* ── pixels / primitives ─────────────────────────────────────────────────── */
void	put_pixel(t_data *d, int x, int y, unsigned int color);
unsigned int	get_pixel(t_data *d, int x, int y);
unsigned int	blend_rgb(unsigned int dst, unsigned int src,
	double a);
	void	put_pixel_blend(t_data *d, int xy[],
	unsigned int color, double a);

	int	key_press(int kc, t_data *d);
	int	key_release(int kc, t_data *d);
	int	close_game(t_data *d);


int	is_key_w(int kc);
int	is_key_s(int kc) ;
int	is_key_a(int kc);
int	is_key_d(int kc);
int	is_key_left(int kc);
int	is_key_right(int kc);
int	is_key_up(int kc) ;
int	is_key_down(int kc);
int	is_key_esc(int kc);
int	is_key_r(int kc);
int	is_key_f(int kc);


void	move_fwd_back(t_data *d, double ms);
void	move_strafe(t_data *d, double ms);
void	rotate_dir_plane(t_data *d, double rs);
void	update_pitch(t_data *d, double dt);
void	move_player(t_data *d, double dt);
void	draw_sky_floor(t_data *d);


void	cast_init(t_data *d, t_cast *c, int col);
void	cast_step_to_hit(t_data *d, t_cast *c);
void	draw_slice_store_hit(t_data *d, t_cast *c, int col);
void	cast_and_draw_column(t_data *d, int col);


void	mm_compute_rect(t_data *d);
void	mm_draw_cells(t_data *d);
void	mm_draw_player_and_head(t_data *d, int *px, int *py);
void	mm_draw_rays(t_data *d, int px, int py);
void	mm_draw_border(t_data *d);
void	draw_minimap_overlay(t_data *d);

int	render_frame(void *param);


void	init_player_camera(t_data *d);
int	init_gfx(t_data *d);
int	alloc_ray_buffers(t_data *d);



#endif
