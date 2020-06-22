/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/30 16:43:37 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/18 17:10:51 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			distance_shader(t_colour *colour, double dist)
{
	if (dist <= 1.)
		return ;
	colour->colour = ((int)(colour->rgb.r / dist) << 16 |
						(int)(colour->rgb.g / dist) << 8 |
						(int)(colour->rgb.b / dist));
}

void			linedraw(t_game *game, t_pos *start, t_pos *end,
							unsigned int colour)
{
	t_pos	save;

	save = *start;
	while (start->x < end->x)
	{
		start->y = save.y;
		while (start->y < end->y)
		{
			pixel_putter(game, start->x, start->y, colour);
			start->y++;
		}
		start->x++;
	}
}

void			pixel_putter(t_game *game, int x, int y, unsigned int colour)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.linesize + (x * (game->img.bpp / 8)));
	*(unsigned int *)dst = colour;
}

unsigned int	tex_pixeliser(t_img *tex, int x, int y)
{
	unsigned int	colour;
	char			*dst;

	y = y > 0 ? y : 0;
	dst = tex->addr + (y * tex->linesize + (x * (tex->bpp / 8)));
	colour = *(unsigned int *)dst;
	return (colour);
}
