/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/30 16:43:37 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/09 14:28:05 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			pixel_putter(t_game *game, int x, int y, unsigned int colour)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.linesize + (x * (game->img.bpp / 8)));
	*(unsigned int *)dst = colour;
}

void			distance_shader(t_colour *colour, double dist)
{
	if (dist <= 1.)
		return ;
	colour->colour = ((int)(colour->rgb.r / dist) << 16 |
						(int)(colour->rgb.g / dist) << 8 |
						(int)(colour->rgb.b / dist));
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
