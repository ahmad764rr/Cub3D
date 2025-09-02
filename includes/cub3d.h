/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahramada <ahramada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:51:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/09/02 17:04:57 by ahramada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../../Cub3D/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"

# define ERO_USA        "Error\nusage: ./cub3d <file.cub>"
# define ERO_NAME_FILE  "Error\nunsupported file"
# define ERO_OPEN_FILE  "Error\nfailed to open file"
# define ERO_MAP        "Error\nmap is invalid"
# define ERO_MALLOC     "Error\nmalloc failed"
# define ERO_CLOSED_MAP "Error\n❌ Map is NOT closed!\n"
# define ERO_FILE       "Error\nThe file is not accessible or doesn't exist"
# define ERO_READ       "Error\nread failed"
# define ERO_CLOSE      "Error\nclose failed"
# define ERO_MLX        "Error\nmlx failed"
# define ERO_MLX_WIN    "Error\nmlx_new_window failed"
# define ERO_MLX_IMG    "Error\nmlx_new_image failed"
# define ERO_MLX_ADDR   "Error\nmlx_get_data_addr failed"
# define ERO_MLX_INIT   "Error\nmlx_init failed"

typedef struct s_map	t_map;
typedef struct s_row	t_row;
typedef struct s_cub3d	t_cub3d;
typedef struct s_player	t_player;
typedef struct s_point	t_point;
typedef struct s_color	t_color;

struct s_player
{
	int			map_x;
	int			map_y;
}	;

struct s_point
{
	int			x;
	int			y;
	int			access;
	int			width;
	int			height;
}	;

struct s_row
{
	int			width;
	int			hight;
}	;

struct s_color
{
	int			r;
	int			g;
	int			b;
};

struct s_map
{
	int			map_width;
	int			map_height;
	int			**visited;
	char		**data;
	char		*file_path;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	char		*texture_sprite;
	t_color		color_floor;
	t_color		color_ceiling;
}	;

struct s_cub3d
{
	int			is_empty;
	int			fd;
	int			flag;
	char		*file_path;
	t_map		map;
	t_player	player;
	t_row		*row_width;
	t_row		*colunm_height;
	t_point		**point;
}	;
char				*valid_set_texture_data(char *line, char *prefix);
void				set_texture_data(char *line, int skip, t_cub3d **cub3d);
void				set_color_data(int value, t_cub3d **cub3d, int which);
int					flood_fill(t_map *map, int x, int y, t_cub3d *cub3d);
int					setup_flood_fill(t_cub3d *cub3d);
int					ft_isspace(char c);
int					check_access(char *line);
int					open_file(t_cub3d **cub3d);
int					is_acceptable_file(char *line, int skip, t_cub3d **cub3d);
int					parsing_manager(t_cub3d **cub3d);
int					open_file_manager(t_cub3d **cub3d);
int					check_map_searching_2(t_cub3d **cub3d,
						char *map_line, int *lock, int *y);
int					comma_handle_color(char *line);
int					find_std_color_formial(char *line, int *lock, int *index);
int					handle_color_formality(char *line);
int					check_values(char *line, t_cub3d **cub3d, int which);
int					handle_color_data(char *line, int skip, t_cub3d **cub3d);
int					check_data_condition_2(char *trimmed_line,
						t_cub3d **cub3d, int *is_complete, int *height);
int					check_data_condition(char *trimmed_line,
						t_cub3d **cub3d, int *is_complete);
int					setup_check_data(char *line, t_cub3d **cub3d,
						int *is_complete);
int					setup_check_map(t_cub3d **cub3d, char **map_line);
int					check_map_values_condtion(t_cub3d **cub3d, char *line,
						int *check_empty);
int					check_map_values(t_cub3d **cub3d, char *line, int y);
int					check_map_condtion(t_cub3d **cub3d, char *map_line,
						int *lock, int *y);
int					check_map_searching(t_cub3d **cub3d, char *map_line,
						int *lock, int *y);
int					check_map(t_cub3d **cub3d);
int					handle_read_file(t_cub3d **cub3d, int *is_complete);
int					read_file(t_cub3d **cub3d);
int					map_status(t_cub3d **cub3d);
int					read_file_handle(t_cub3d **cub3d, char *line);
void				handle_get_next_line(int fd, char *line);
void				check_name(t_cub3d *cub3d);
void				free_texture(t_cub3d *cub3d);
void				init_cub3d(t_cub3d *cub3d, char *arg);
void				handle_error(char *_error);
void				check_data_error(t_cub3d **cub3d, char *message, int flag);
void				free_map_points(t_cub3d *cub3d);
void				set_map_values(t_cub3d **cub3d, char *line, int y);

#endif