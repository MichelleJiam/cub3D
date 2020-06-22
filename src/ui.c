/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 13:02:22 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/18 18:25:16 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	numstr_maker(char *str, int n, int *start)
{
	int		tmp;
	int		nc;

	tmp = n;
	nc = (n == 0) ? 1 : 0;
	if (n == 0)
		str[*start] = n + '0';
	else
	{
		while (tmp)
		{
			tmp /= 10;
			nc++;
		}
		tmp = nc > 0 ? nc - 1 : 0;
		while (n > 0)
		{
			str[*start + tmp] = (n % 10) + '0';
			n /= 10;
			tmp--;
		}
	}
	*start += nc;
}

void	string_putter(char *str, char *src, int *start)
{
	int i;

	i = 0;
	while (src[i])
	{
		str[*start + i] = src[i];
		i++;
	}
	*start += i;
}

void	quest_master(t_game *game, t_pos *start)
{
	char	str[50];
	int		i;

	i = 0;
	while (i < 50)
	{
		str[i] = 0;
		i++;
	}
	i = 0;
	string_putter(str, "Stars found: ", &i);
	numstr_maker(str, game->player.quest - game->map.spritenum, &i);
	string_putter(str, " / ", &i);
	numstr_maker(str, game->player.quest, &i);
	mlx_string_put(game->mlx, game->mlx_win, start->x,
					start->y, 0xFFDA0B, str);
}

void	minimapper(t_game *game, t_pos *start, t_pos *end)
{
	int				x;
	int				y;
	unsigned int	colour;

	x = 0;
	while (x < game->map.cols)
	{
		y = 0;
		while (y < game->map.rows)
		{
			start->x = (int)(end->x - (game->map.cols * 5) + (x * 5));
			start->y = (int)(end->y - (game->map.rows * 5) + (y * 5));
			if (game->map.data[y][x] == '1')
				colour = 0x2E4D62;
			else if (y == (int)game->player.pos.y &&
						x == (int)game->player.pos.x)
				colour = 0xFFDA0B;
			else
				colour = 0x8DA8AF;
			linedraw(game, start, end, colour);
			y++;
		}
		x++;
	}
}

void	ui_drawer(t_game *game)
{
	t_pos	mapstart;
	t_pos	mapend;
	t_pos	qtstart;

	if (game->config.screenwidth < 250 || game->config.screenheight < 250)
		return ;
	mapend.x = (int)(game->config.screenwidth * 0.9);
	mapend.y = (int)(game->config.screenheight * 0.9);
	qtstart.x = (int)(game->config.screenwidth * 0.05);
	qtstart.y = (int)(game->config.screenheight * 0.05);
	minimapper(game, &mapstart, &mapend);
	if (game->map.star)
		quest_master(game, &qtstart);
}
