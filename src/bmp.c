/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 22:40:28 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/08 14:47:59 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	shiftnwrite(unsigned char *str, int n)
{
	str[0] = (unsigned char)(n);
	str[1] = (unsigned char)(n >> 8);
	str[2] = (unsigned char)(n >> 16);
	str[3] = (unsigned char)(n >> 24);
}

void	data_writer(t_game *game)
{
	int				x;
	int				y;
	t_colour		colour;

	y = game->config.screenheight - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < game->config.screenwidth)
		{
			colour.colour = tex_pixeliser(&game->fr1, x, y);
			write(game->save, &colour.colour, 3);
			write(game->save, "0x00", 1);
			x++;
		}
		y--;
	}
}

void	header_writer(t_game *game)
{
	int				i;
	int				n;
	unsigned char	buffer[54];

	i = 0;
	n = 0;
	while (i < 54)
	{
		buffer[i] = (unsigned char)(0);
		i++;
	}
	buffer[0] = (unsigned char)('B');
	buffer[1] = (unsigned char)('M');
	n = game->config.screenwidth * game->config.screenheight * 4 + 54;
	shiftnwrite(buffer + 2, n);
	buffer[10] = (unsigned char)(54);
	buffer[14] = (unsigned char)(40);
	n = game->config.screenwidth;
	shiftnwrite(buffer + 18, n);
	n = game->config.screenheight;
	shiftnwrite(buffer + 22, n);
	buffer[26] = (unsigned char)(1);
	buffer[28] = (unsigned char)(32);
	write(game->save, buffer, 54);
}

void	screensaver(t_game *game)
{
	header_writer(game);
	data_writer(game);
	close(game->save);
	exiter(game, 0);
}
