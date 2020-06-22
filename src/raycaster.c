/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 17:19:50 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/19 13:51:11 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	tex_measurer(t_game *game, t_view *view, t_img *tex, double perpdist)
{
	if (!view->side)
		view->wallhit = game->player.pos.y + perpdist * game->view.raydir.y;
	else
		view->wallhit = game->player.pos.x + perpdist * game->view.raydir.x;
	view->wallhit -= floor(view->wallhit);
	tex->pos.x = (int)(view->wallhit * tex->width);
	if ((!view->side && view->raydir.x > 0) ||
		(view->side && view->raydir.y < 0))
		tex->pos.x = tex->width - tex->pos.x - 1;
	tex->t_step.y = 1. * tex->height / view->line.height;
	tex->pos.y = (view->line.start - game->config.screenheight / 2 +
					view->line.height / 2) * tex->t_step.y;
}

void	outliner(t_game *game, t_line *line, double perpdist)
{
	line->height = (int)(game->config.screenheight / perpdist);
	line->start = game->config.screenheight / 2 - (line->height / 2);
	if (line->start < 0)
		line->start = 0;
	line->end = line->height / 2 + game->config.screenheight / 2;
	if (line->end < 0)
		line->end = game->config.screenheight;
	if (line->end >= game->config.screenheight)
		line->end = game->config.screenheight - 1;
}

void	ddanalyser(t_game *game, t_view *view)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (view->sidedist.x < view->sidedist.y)
		{
			view->sidedist.x += view->deltadist.x;
			view->raypos.x += view->step.x;
			view->side = 0;
		}
		else
		{
			view->sidedist.y += view->deltadist.y;
			view->raypos.y += view->step.y;
			view->side = 1;
		}
		if (view->raypos.y < 0 || view->raypos.x < 0 ||
			game->map.data[(int)view->raypos.y][(int)view->raypos.x] == '1')
			hit = 1;
	}
}

void	dist_marker(t_game *game, t_view *view)
{
	view->deltadist.x = fabs(1. / view->raydir.x);
	view->deltadist.y = fabs(1. / view->raydir.y);
	if (view->raydir.x < 0)
	{
		pos_setter(&view->step, -1, (view->raydir.y < 0) ? -1 : 1);
		view->sidedist.x = (game->player.pos.x - view->raypos.x)
							* view->deltadist.x;
	}
	else
	{
		pos_setter(&view->step, 1, (view->raydir.y < 0) ? -1 : 1);
		view->sidedist.x = (view->raypos.x + 1 - game->player.pos.x)
							* view->deltadist.x;
	}
	if (view->raydir.y < 0)
		view->sidedist.y = (game->player.pos.y - view->raypos.y)
							* view->deltadist.y;
	else
		view->sidedist.y = (view->raypos.y + 1 - game->player.pos.y)
							* view->deltadist.y;
}

void	viewfinder(t_game *game, t_view *view, int x, t_img *tex)
{
	view->camera_x = (2 * x / (double)game->config.screenwidth) - 1;
	view->raydir.x = view->dir.x + view->plane.x * view->camera_x;
	view->raydir.y = view->dir.y + view->plane.y * view->camera_x;
	dist_marker(game, view);
	ddanalyser(game, view);
	if (!view->side)
	{
		game->map.perpdist[x] = fabs((view->raypos.x - game->player.pos.x +
								(1. - view->step.x) / 2.) / view->raydir.x);
		*tex = view->raydir.x < 0 ? game->config.tex[E] : game->config.tex[W];
	}
	else
	{
		game->map.perpdist[x] = fabs((view->raypos.y - game->player.pos.y +
								(1. - view->step.y) / 2.) / view->raydir.y);
		*tex = view->raydir.y < 0 ? game->config.tex[S] : game->config.tex[N];
	}
}
