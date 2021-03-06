/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:25:18 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/18 18:32:59 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mover_lr(t_game *game, t_player *player, t_view *view, int dir)
{
	t_pos	newpos;

	newpos.x = player->pos.x + (dir * 3.5) * (view->plane.x * MOVE);
	newpos.y = player->pos.y + (dir * 3.5) * (view->plane.y * MOVE);
	if ((int)floor(newpos.x) > 0 && (int)floor(newpos.x) < game->map.cols &&
		game->map.data[(int)player->pos.y][(int)newpos.x] == '0')
		player->pos.x = newpos.x;
	if ((int)floor(newpos.y) > 0 && (int)floor(newpos.y) < game->map.rows &&
		game->map.data[(int)newpos.y][(int)player->pos.x] == '0')
		player->pos.y = newpos.y;
	if (game->map.data[(int)newpos.y][(int)newpos.x] == '2' &&
		game->map.star == 1)
	{
		player->pos.x = newpos.x;
		player->pos.y = newpos.y;
		game->map.data[(int)player->pos.y][(int)player->pos.x] = '0';
		game->map.spritenum--;
		sprite_zapper(&game->map.sprites, player->pos);
	}
}

void	mover_ud(t_game *game, t_player *player, t_view *view, int dir)
{
	t_pos	newpos;

	newpos.x = player->pos.x + (dir * 3.5) * (view->dir.x * MOVE);
	newpos.y = player->pos.y + (dir * 3.5) * (view->dir.y * MOVE);
	if ((int)floor(newpos.x) > 0 && (int)floor(newpos.x) < game->map.cols &&
		game->map.data[(int)player->pos.y][(int)newpos.x] == '0')
		player->pos.x = newpos.x;
	if ((int)floor(newpos.y) > 0 && (int)floor(newpos.y) < game->map.rows &&
		game->map.data[(int)newpos.y][(int)player->pos.x] == '0')
		player->pos.y = newpos.y;
	if (game->map.data[(int)newpos.y][(int)newpos.x] == '2' &&
		game->map.star == 1)
	{
		player->pos.x = newpos.x;
		player->pos.y = newpos.y;
		game->map.data[(int)player->pos.y][(int)player->pos.x] = '0';
		game->map.spritenum--;
		sprite_zapper(&game->map.sprites, player->pos);
	}
}

void	turner(t_view *view, int d)
{
	t_pos	plane;
	t_pos	dir;

	plane.x = view->plane.x * cos(d * TURN) + view->plane.y * -sin(d * TURN);
	plane.y = view->plane.x * sin(d * TURN) + view->plane.y * cos(d * TURN);
	dir.x = view->dir.x * cos(d * TURN) + view->dir.y * -sin(d * TURN);
	dir.y = view->dir.x * sin(d * TURN) + view->dir.y * cos(d * TURN);
	view->dir = dir;
	view->plane = plane;
}

int		keyrelease(int keycode, t_game *game)
{
	if (keycode == MV_UP)
		game->keys.key_up = 0;
	if (keycode == MV_DW)
		game->keys.key_dw = 0;
	if (keycode == MV_LF)
		game->keys.key_lf = 0;
	if (keycode == MV_RT)
		game->keys.key_rt = 0;
	if (keycode == LEFT)
		game->keys.key_rotl = 0;
	if (keycode == RIGHT)
		game->keys.key_rotr = 0;
	return (0);
}

int		keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		exiter(game, 0);
	if (keycode == MV_UP)
		game->keys.key_up = 1;
	if (keycode == MV_DW)
		game->keys.key_dw = 1;
	if (keycode == MV_LF)
		game->keys.key_lf = 1;
	if (keycode == MV_RT)
		game->keys.key_rt = 1;
	if (keycode == LEFT)
		game->keys.key_rotl = 1;
	if (keycode == RIGHT)
		game->keys.key_rotr = 1;
	return (0);
}
