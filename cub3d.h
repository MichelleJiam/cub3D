/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 13:35:21 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/18 18:32:49 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include "./gnl/get_next_line.h"
# include "./minilibx/mlx.h"

# define MV_UP 13
# define MV_DW 1
# define MV_LF 0
# define MV_RT 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

# define TURN 0.03
# define MOVE 0.025

typedef enum		e_form
{
	nofile = -1, xpm = 0, png = 1
}					t_form;

typedef	enum		e_dir
{
	NONE = -1, N, S, E, W, F, C
}					t_dir;

typedef struct		s_key
{
	unsigned int	key_up;
	unsigned int	key_dw;
	unsigned int	key_lf;
	unsigned int	key_rt;
	unsigned int	key_rotl;
	unsigned int	key_rotr;
}					t_key;

typedef struct		s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgb;

typedef union		u_colour
{
	unsigned int	colour;
	t_rgb			rgb;
}					t_colour;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_player
{
	t_pos			pos;
	t_dir			startdir;
	int				quest;
}					t_player;

typedef struct		s_render
{
	t_pos			transform;
	int				screenx;
	t_pos			start;
	double			start0;
	t_pos			end;
	t_pos			dim;
	t_colour		col;
}					t_render;

typedef struct		s_cfloor
{
	t_pos			pos;
	t_pos			fstart;
}					t_cfloor;

typedef struct		s_line
{
	int				height;
	int				start;
	int				end;
}					t_line;

typedef	struct		s_view
{
	int				side;
	double			camera_x;
	double			fsdist;
	double			wallhit;
	t_pos			deltadist;
	t_pos			dir;
	t_pos			plane;
	t_pos			raydir;
	t_pos			raypos;
	t_pos			sidedist;
	t_pos			step;
	t_line			line;
}					t_view;

typedef struct		s_sprite
{
	t_pos			pos;
	double			dist;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_map
{
	char			**data;
	int				cols;
	int				rows;
	int				spritenum;
	int				star;
	double			*perpdist;
	t_sprite		*sprites;
}					t_map;

typedef struct		s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				linesize;
	int				endian;
	int				width;
	int				height;
	t_pos			t_step;
	t_pos			pos;
}					t_img;

typedef struct		s_config
{
	int				i;
	int				map_found;
	t_img			tex[6];
	t_img			sprite;
	t_colour		floor;
	t_colour		ceiling;
	intmax_t		screenwidth;
	intmax_t		screenheight;
}					t_config;

typedef struct		s_game
{
	void			*mlx_win;
	void			*mlx;
	int				save;
	unsigned short	frame;
	t_img			img;
	t_img			fr1;
	t_img			fr2;
	t_key			keys;
	t_config		config;
	t_map			map;
	t_view			view;
	t_player		player;
}					t_game;

/*
** cub3d
*/
int					updater(t_game *game);
void				init_mlx(t_game *game);

/*
** init
*/
void				init_view(t_view *view);
void				init_config(t_config *config);
void				init_key(t_key *keys);
void				init_img(t_img *img);
int					init_game(t_game *game, int save);

/*
** check
*/
void				config_checker(t_game *game);
int					map_checker(t_game *game, char **map, int x, int y);
int					file_checker(int case_n, void *param);
int					arg_checker(t_game *game, int argc, char **argv);

/*
** parser
*/
void				map_copier(t_game *game, char **map);
int					finish_parse(t_game *game);
int					fc_filler(t_game *game, char *line, int *i);
int					data_filler(t_game *game, char *line);
int					parser(t_game *game, char *map);

/*
** config
*/
int					colour_setter(t_game *game, t_colour *element,
									char *line, int *i);
int					res_setter(t_game *game, char *line, int *i);
void				tex_filer(t_game *game, char *path, t_img *tex);
char				*pathfinder(char *line, int *i, int len);
int					tex_setter(t_game *game, t_img *tex, char *line, int *i);

/*
** map
*/
void				init_map(t_map *map);
void				start_setter(t_game *game, char direction, int x, int y);
void				map_reader(t_game *game, char **str, int col, int row);
char				*map_writer(t_game *game, char *line, int *i);
int					map_maker(t_game *game, char *line, int *i);

/*
** input
*/
void				mover_lr(t_game *game, t_player *player,
								t_view *view, int dir);
void				mover_ud(t_game *game, t_player *player,
								t_view *view, int dir);
void				turner(t_view *view, int d);
int					keyrelease(int keycode, t_game *game);
int					keypress(int keycode, t_game *game);

/*
** raycaster
*/
void				tex_measurer(t_game *game, t_view *view,
									t_img *tex, double perpdist);
void				outliner(t_game *game, t_line *line, double perpdist);
void				ddanalyser(t_game *game, t_view *view);
void				dist_marker(t_game *game, t_view *view);
void				viewfinder(t_game *game, t_view *view, int x, t_img *tex);

/*
** render
*/
void				wall_drawer(t_game *game, t_line *line,
								int x, t_img *tex);
void				fc_measurer(t_game *game, t_cfloor *fc, int y, int x);
void				fc_drawer(t_game *game, t_img *tex, int x, int height);
int					render_map(t_game *game);

/*
** colour
*/
void				distance_shader(t_colour *colour, double dist);
void				linedraw(t_game *game, t_pos *start, t_pos *end,
							unsigned int colour);
void				pixel_putter(t_game *img, int x, int y,
									unsigned int colour);

unsigned int		tex_pixeliser(t_img *tex, int x, int y);

/*
** sprite
*/
void				sprite_zapper(t_sprite **list, t_pos pos);
void				sprite_drawer(t_game *game, t_sprite *sprite,
									t_render *sp, t_img *tex);
void				sprite_measurer(t_game *game, t_render *sp);
void				sprite_transformer(t_game *game, t_sprite *sprite,
										t_render *sp);
void				sprite_summoner(t_game *game);

/*
** ui
*/
void				numstr_maker(char *str, int n, int *start);
void				string_putter(char *str, char *src, int *start);
void				quest_master(t_game *game, t_pos *start);
void				minimapper(t_game *game, t_pos *start, t_pos *end);
void				ui_drawer(t_game *game);

/*
** bmp
*/
void				shiftnwrite(unsigned char *str, int n);
void				data_writer(t_game *game);
void				header_writer(t_game *game);
void				screensaver(t_game *game);

/*
** sort
*/
t_sprite			*mergelist(t_sprite *sprites_a, t_sprite *sprites_b);
void				splitlist(t_sprite *sprites_a, t_sprite **sprites_b);
t_sprite			*mergesorter(t_sprite *sprites);
t_sprite			*sprite_sorter(t_game *game, t_sprite *sprites);
void				sprite_lister(t_game *game, t_sprite **list, int x, int y);

/*
** utils
*/
void				pos_setter(t_pos *pos, double x, double y);
int					inset(char *line, int i);
int					isnumber(char *line, int i);
int					value_finder(char *line, int *i, char exc);
int					whitespaceskip(char *line, int *i);

/*
** utils2
*/
intmax_t			ft_atoi(char *line, int *i);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);

/*
** exit
*/
void				sprite_evicter(t_sprite **list);
void				tex_cleaner(t_game *game, t_img *tex);
void				map_cleaner(char **map);
int					exiter(t_game *game, int c);
void				err_handler(t_game *game, char *str);

#endif
