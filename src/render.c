/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 15:47:04 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/09 14:53:08 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_drawer(t_game *game, t_line *line, int x, t_img *tex)
{
	int			i;
	int			end;
	t_colour	colour;

	i = game->config.ceiling.colour ? 0 : line->start;
	end = game->config.floor.colour ? game->config.screenheight : line->end;
	colour.colour = 0;
	while (i < end)
	{
		if (i < line->start)
			pixel_putter(game, x, i, game->config.ceiling.colour);
		else if (i >= line->end)
			pixel_putter(game, x, i, game->config.floor.colour);
		else
		{
			colour.colour = tex_pixeliser(tex, tex->pos.x, tex->pos.y);
			distance_shader(&colour, (game->map.perpdist[x] / 2.5));
			pixel_putter(game, x, i, colour.colour);
			tex->pos.y += tex->t_step.y;
		}
		i++;
	}
}

void	fc_measurer(t_game *game, t_cfloor *fc, int y, int x)
{
	double	weight;
	t_view	*view;

	view = &game->view;
	if (!view->side && view->raydir.x > 0 && y == view->line.end)
		pos_setter(&fc->fstart, view->raypos.x,
					view->raypos.y + view->wallhit);
	else if (!view->side && view->raydir.x < 0 && y == view->line.end)
		pos_setter(&fc->fstart, view->raypos.x + 1.,
					view->raypos.y + view->wallhit);
	else if (view->side && view->raydir.y > 0 && y == view->line.end)
		pos_setter(&fc->fstart, view->raypos.x + view->wallhit,
					view->raypos.y);
	else if (view->side && view->raydir.y < 0 && y == view->line.end)
		pos_setter(&fc->fstart, view->raypos.x + view->wallhit,
					view->raypos.y + 1.);
	view->fsdist = game->config.screenheight /
					(2. * y - game->config.screenheight);
	weight = view->fsdist / game->map.perpdist[x];
	fc->pos.x = weight * fc->fstart.x + (1. - weight) * game->player.pos.x;
	fc->pos.y = weight * fc->fstart.y + (1. - weight) * game->player.pos.y;
}

void	fc_drawer(t_game *game, t_img *tex, int x, int height)
{
	int			y;
	t_cfloor	fc;
	t_colour	colour;

	y = game->view.line.end;
	while (y < game->config.screenheight)
	{
		fc_measurer(game, &fc, y, x);
		tex->pos.x = (int)(fc.pos.x * tex->width) % tex->width;
		tex->pos.y = (int)(fc.pos.y * tex->height) % tex->height;
		colour.colour = tex_pixeliser(tex, tex->pos.x, tex->pos.y);
		distance_shader(&colour, (game->view.fsdist / 2.5));
		if (height != 0)
			pixel_putter(game, x, height - y, colour.colour);
		else
			pixel_putter(game, x, y, colour.colour);
		y++;
	}
}

int		render_map(t_game *game)
{
	int			x;
	t_img		tex;

	x = 0;
	game->img = (game->frame % 2) ? game->fr1 : game->fr2;
	while (x < game->config.screenwidth)
	{
		pos_setter(&game->view.raypos, (int)game->player.pos.x,
					(int)game->player.pos.y);
		viewfinder(game, &game->view, x, &tex);
		outliner(game, &game->view.line, game->map.perpdist[x]);
		tex_measurer(game, &game->view, &tex, game->map.perpdist[x]);
		if (game->config.tex[F].ptr)
			fc_drawer(game, &game->config.tex[F], x, 0);
		if (game->config.tex[C].ptr)
			fc_drawer(game, &game->config.tex[C], x,
						game->config.screenheight);
		wall_drawer(game, &game->view.line, x, &tex);
		x++;
	}
	sprite_summoner(game);
	if (game->save)
		screensaver(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.ptr, 0, 0);
	return (0);
}
