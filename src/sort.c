/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 17:46:07 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/11 18:22:30 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	*mergelist(t_sprite *sprites_a, t_sprite *sprites_b)
{
	if (!sprites_a)
		return (sprites_b);
	if (!sprites_b)
		return (sprites_a);
	if (sprites_a->dist > sprites_b->dist)
	{
		sprites_a->next = mergelist(sprites_a->next, sprites_b);
		return (sprites_a);
	}
	else
	{
		sprites_b->next = mergelist(sprites_a, sprites_b->next);
		return (sprites_b);
	}
}

void		splitlist(t_sprite *sprites_a, t_sprite **sprites_b)
{
	t_sprite	*fast;
	t_sprite	*slow;

	fast = sprites_a;
	slow = sprites_a;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	*sprites_b = slow->next;
	slow->next = NULL;
}

t_sprite	*mergesorter(t_sprite *sprites)
{
	t_sprite	*sprites_b;

	if (!sprites || !sprites->next)
		return (sprites);
	splitlist(sprites, &sprites_b);
	sprites = mergesorter(sprites);
	sprites_b = mergesorter(sprites_b);
	return (mergelist(sprites, sprites_b));
}

t_sprite	*sprite_sorter(t_game *game, t_sprite *sprites)
{
	t_sprite	*list;
	t_pos		pos;
	t_pos		relpos;

	list = sprites;
	pos_setter(&pos, game->player.pos.x, game->player.pos.y);
	while (sprites)
	{
		relpos.x = pos.x - sprites->pos.x;
		relpos.y = pos.y - sprites->pos.y;
		sprites->dist = (relpos.x * relpos.x + relpos.y * relpos.y);
		sprites = sprites->next;
	}
	list = mergesorter(list);
	return (list);
}
