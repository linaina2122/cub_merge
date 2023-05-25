/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:20:43 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/25 19:52:20 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h> //?
# include <math.h>
# include "../libft/includes/libft.h"

# define EXT_CUB ".cub"
# define EXT_XPM ".xpm"

//*PARSING
# define ERR_NUM_ARG "Incorrect number of arguments\n"
# define ERR_WRG_EXT "Incorrect file extension\n"
# define ERR_OPN_FIL "Cannot open given file\n"
# define ERR_ISA_DIR "Argument is a directory\n"
# define ERR_WRG_SCN "Incorrect scene configuration\n"
# define ERR_FA_CONV "Failed converting the xpm file to image\n"

//*GNL
# define BUFFER_SIZE 1
//*********************

# define SCALE 64
# define WIDTH 1920
# define HEIGHT 1080
//RAY

# define NUM_RAYS WIDTH 
//*******************************************************
//*PARSING PART
typedef struct s_map_tools
{
	int		fd;
	int		dupe;
	int		flags;
	char	*line;
	char	**unchecked_map;
	int		i;
	int		j;
}	t_map_tools;

typedef struct s_map
{
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
	char					**layout;
	double					s_dir;
	unsigned int			*f;
	unsigned int			*c;
	int						dim[2];
	size_t					pos[2];
	t_map_tools				*tools;
}	t_map;

//*ERROR CHECKING
//* main
void	error_checks(int ac, char **av, t_map *map);

//*features_checks
void	check_each(char *line, int *flags, t_map *map);

//*map_loops
int		check_scene(char *file, t_map *map);

//*map_loop_utils
void	fill_rest(char *line, int max, int *dupe, char *uncheck);
int		within_walls(char **map, int i, int j);
int		check_ends(char *line);

//*features_utils
double	player_orientation(char player_start);

//*check_utils
int		check_extension(char *feature, char *ext);
int		check_file(char *file);
int		empty_line(char *line, int *dimh, int *dimw);
int		check_nums(char **feature);
char	**check_end_spaces(char *line, int *flags);

//*darr_utils
void	free_darr(char **darr);
int		len_darr(char **darr);

//*GNL
char	*get_next_line(int fd);

//*******************************************************
//*errors
void	err_arg(char *custom_err_msg);

//*******************************************************
//*2D MAP
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_text{
	void			*n_img;
	void			*img;
	void			*w_img;
	void			*o_img;
	void			*s_img;
	unsigned int	*addr;
	int				bpp;
	int				line_length;
	int				endian;
}t_text;

typedef struct s_ray {
	double	xstep;
	double	ystep;
	double	xfirstintersecpointhor;
	double	yfirstintersecpointhor;
	double	xfirstintersecpointver;
	double	yfirstintersecpointver;
	double	rayangle;
	double	next_h_interx;
	double	next_h_intery;
	double	next_v_interx;
	double	next_v_intery;
	double	wallstrip;
	double	howallx;
	double	howally;
	double	vwallx;
	double	vwally;
	int		hflag;
	int		vflag;
	double	final_distance;
	short	is_it_verticale;
	double	wallstripeheight;
	int		top_of_wall;
	int		end_of_wall;
	int		index;
}t_ray;

typedef struct s_my_struct{
	int				keycode;
	int				map_width;
	int				map_height;
	char			**map;
	void			*mlx_ptr;
	void			*win_ptr;
	double			player_x;
	double			player_y;
	double			rot_player_x;
	double			rot_player_y;
	double			rot_angle;
	double			var;
	int				move[3];
	unsigned int	ceil_col;
	unsigned int	floor_col;
	double			speed;
	double			fov_angle;
	int				flag;
	t_data			imge;
	t_text			t;
	t_ray			*r;
}t_my_struct;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

int		loop_func(t_my_struct *m);
void	player_init(t_my_struct *m);
void	draw(t_my_struct *m);
int		mouvements_press(int keycode, t_my_struct *m);
int		mouvements_release(int keycode, t_my_struct *m);
void	window(t_my_struct *m, t_map *map);
void	ft_put_pixel(t_my_struct *data, int x, int y, int color);
void	data_struct_init(t_my_struct *data);
int		move_up(t_my_struct *m);
int		move_down(t_my_struct *m);
int		right_move(t_my_struct *m);
int		left_move(t_my_struct *m);
int		find_wall(double x, double y, t_my_struct *m);
void	h_intercept(t_my_struct *m, double angle);
t_ray	*struct_init(t_my_struct *m);
void	ray_angles(t_my_struct *m);
double	normalize_angle(double angl);
void	v_intercept(t_my_struct *m, double angle);
void	h_intercept(t_my_struct *m, double angle);
void	rander(t_my_struct *m);
void	find_h_wall(t_my_struct *m);
void	find_v_wall(t_my_struct *m);
void	renderwalls(t_my_struct *m, double ray_angle);
void	walls(t_my_struct *m, int count);
void	get_distance(t_my_struct *m);
int		check_left_right(double angle);
int		check_up_down(double angle);
double	distance_of_two_points(t_my_struct *m, double d1, double d2);
int		exiting(int keycode, t_my_struct *m);
int		update(t_my_struct *m);
void	text_init(t_my_struct *m, t_map *t);
 void	text_initttt(t_my_struct *m, float ray_angle);

//*******************************************************
#endif