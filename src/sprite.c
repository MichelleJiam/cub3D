/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 17:17:32 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/11 18:36:59 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_lister(t_game *game, t_sprite **list, int x, int y)
{
	t_sprite *new;

	new = (t_sprite *)malloc(sizeof(t_sprite));
	if (!new)
		err_handler(game, "Malloc fail\n");
	pos_setter(&new->pos, x + 0.5, y + 0.5);
	new->dist = 0;
	if (!list)
		new->next = NULL;
	else
	{
		new->next = *list;
	}
	*list = new;
}

void	sprite_drawer(t_game *game, t_sprite *sprite, t_render *sp, t_img *tex)
{
	int			f;

	sp->start0 = sp->start.y;
	while (sp->start.x < sp->end.x)
	{
		tex->pos.x = (int)(256 * (sp->start.x - (-sp->dim.x / 2
						+ sp->screenx)) * tex->width / sp->dim.x) / 256;
		if (sp->transform.y > 0 && sp->transform.y <
			game->map.perpdist[(int)sp->start.x])
		{
			sp->start.y = sp->start0;
			while (sp->start.y < sp->end.y)
			{
				f = sp->start.y * 2 - game->config.screenheight + sp->dim.y;
				tex->pos.y = ((f * tex->height) / sp->dim.y) / 2;
				sp->col.colour = tex_pixeliser(tex, tex->pos.x, tex->pos.y);
				distance_shader(&sp->col, sprite->dist / 3);
				if (sp->col.colour)
					pixel_putter(game, sp->start.x,
									sp->start.y, sp->col.colour);
				sp->start.y++;
			}
		}
		sp->start.x++;
	}
}

void	sprite_measurer(t_game *game, t_render *sp)
{
	sp->dim.y = abs((int)(game->config.screenheight / sp->transform.y));
	sp->dim.x = abs((int)(game->config.screenheight / sp->transform.y));
	sp->start.y = (int)(-sp->dim.y / 2 + game->config.screenheight / 2);
	sp->start.x = (int)(-sp->dim.x / 2 + sp->screenx);
	if (sp->start.y < 0)
		sp->start.y = 0;
	if (sp->start.x < 0)
		sp->start.x = 0;
	sp->end.y = (int)(sp->dim.y / 2 + game->config.screenheight / 2);
	sp->end.x = (int)(sp->dim.x / 2 + sp->screenx);
	if (sp->end.y >= game->config.screenheight)
		sp->end.y = game->config.screenheight - 1.;
	if (sp->end.x >= game->config.screenwidth)
		sp->end.x = game->config.screenwidth - 1.;
}

void	sprite_transformer(t_game *game, t_sprite *sprite, t_render *sp)
{
	t_pos	relpos;
	double	inv_cam;

	inv_cam = 1. / (game->view.plane.x * game->view.dir.y -
				game->view.dir.x * game->view.plane.y);
	relpos.x = sprite->pos.x - game->player.pos.x;
	relpos.y = sprite->pos.y - game->player.pos.y;
	sp->transform.x = inv_cam * (game->view.dir.y * relpos.x -
								game->view.dir.x * relpos.y);
	sp->transform.y = inv_cam * (-game->view.plane.y * relpos.x +
								game->view.plane.x * relpos.y);
}

void	sprite_summoner(t_game *game)
{
	t_render	sp;
	t_sprite	*sprite;

	game->map.sprites = sprite_sorter(game, game->map.sprites);
	sprite = game->map.sprites;
	while (sprite)
	{
		sprite_transformer(game, sprite, &sp);
		sp.screenx = (int)((game->config.screenwidth / 2) *
						(1. + sp.transform.x / sp.transform.y));
		sprite_measurer(game, &sp);
		sprite_drawer(game, sprite, &sp, &game->config.sprite);
		sprite = sprite->next;
	}
}
