/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:40:58 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/19 14:27:48 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_view(t_view *view)
{
	view->side = 0;
	view->camera_x = 0;
	view->fsdist = 0;
	view->wallhit = 0;
	view->line.height = 0;
	view->line.start = 0;
	view->line.end = 0;
	pos_setter(&view->deltadist, 0, 0);
	pos_setter(&view->dir, 0, 0);
	pos_setter(&view->plane, 0, 0);
	pos_setter(&view->raydir, 0, 0);
	pos_setter(&view->raypos, 0, 0);
	pos_setter(&view->sidedist, 0, 0);
	pos_setter(&view->step, 0, 0);
}

void	init_config(t_config *config)
{
	config->i = 0;
	config->map_found = 0;
	init_img(&config->tex[N]);
	init_img(&config->tex[S]);
	init_img(&config->tex[E]);
	init_img(&config->tex[W]);
	init_img(&config->tex[F]);
	init_img(&config->tex[C]);
	init_img(&config->sprite);
	config->floor.colour = 2147483648;
	config->ceiling.colour = 2147483648;
	config->screenwidth = 0;
	config->screenheight = 0;
}

void	init_key(t_key *keys)
{
	keys->key_up = 0;
	keys->key_dw = 0;
	keys->key_lf = 0;
	keys->key_rt = 0;
	keys->key_rotl = 0;
	keys->key_rotr = 0;
}

void	init_img(t_img *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->linesize = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
	pos_setter(&img->t_step, 0, 0);
	pos_setter(&img->pos, 0, 0);
}

int		init_game(t_game *game, int save)
{
	game->mlx_win = NULL;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (-1);
	if (save)
		game->save = open("screenshot.bmp",
						O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else
		game->save = 0;
	if (game->save < 0)
		err_handler(game, "Failed to open screenshot file\n");
	game->frame = 1;
	game->player.startdir = NONE;
	game->player.quest = 0;
	pos_setter(&game->player.pos, 0, 0);
	init_img(&game->img);
	init_img(&game->fr1);
	init_img(&game->fr2);
	init_key(&game->keys);
	init_config(&game->config);
	init_map(&game->map);
	init_view(&game->view);
	return (0);
}
