/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/14 15:52:58 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/11 18:17:22 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_map(t_map *map)
{
	map->data = NULL;
	map->cols = 0;
	map->rows = 0;
	map->spritenum = 0;
	map->sprites = NULL;
	map->perpdist = NULL;
}

void	start_setter(t_game *game, char direction, int x, int y)
{
	pos_setter(&game->player.pos, x + 0.5, y + 0.5);
	if (direction == 'N')
	{
		game->player.startdir = N;
		pos_setter(&game->view.dir, 0, -1);
		pos_setter(&game->view.plane, 0.66, 0);
	}
	else if (direction == 'S')
	{
		game->player.startdir = S;
		pos_setter(&game->view.dir, 0, 1);
		pos_setter(&game->view.plane, -0.66, 0);
	}
	else if (direction == 'E')
	{
		game->player.startdir = E;
		pos_setter(&game->view.dir, 1, 0);
		pos_setter(&game->view.plane, 0, 0.66);
	}
	else
	{
		game->player.startdir = W;
		pos_setter(&game->view.dir, -1, 0);
		pos_setter(&game->view.plane, 0, -0.66);
	}
}

void	map_reader(t_game *game, char **str, int col, int row)
{
	if ((*str)[col] == 'N' || (*str)[col] == 'S' ||
		(*str)[col] == 'E' || (*str)[col] == 'W')
	{
		if (game->player.startdir != NONE)
			err_handler(game, "Multiple starting positions\n");
		start_setter(game, (*str)[col], col, row);
		(*str)[col] = '0';
	}
	else if ((*str)[col] == '2')
	{
		game->map.spritenum++;
		sprite_lister(game, &game->map.sprites, col, row);
	}
	else
	{
		free(*str);
		err_handler(game, "Invalid character in map\n");
	}
}

char	*map_writer(t_game *game, char *line, int *i)
{
	char	*str;
	int		j;
	int		end;

	j = *i;
	while (line[j])
		j++;
	end = j;
	game->map.cols = j > game->map.cols ? j : game->map.cols;
	str = malloc(sizeof(char) * (game->map.cols + 1));
	if (!str)
		err_handler(game, "Malloc fail\n");
	j = 0;
	while (j < game->map.cols)
	{
		str[j] = (j < end) ? line[j] : ' ';
		if (j < end && line[j] && line[j] != '0' &&
				line[j] != '1' && line[j] != ' ')
			map_reader(game, &str, j, game->map.rows);
		j++;
	}
	str[j] = '\0';
	return (str);
}

int		map_maker(t_game *game, char *line, int *i)
{
	char	**tmp;
	int		r;

	if (game->config.i < 8)
		config_checker(game);
	game->config.map_found = 1;
	r = 0;
	tmp = malloc(sizeof(char *) * (game->map.rows + 2));
	if (!tmp)
		err_handler(game, "Malloc fail\n");
	while (r < game->map.rows)
	{
		tmp[r] = ft_strdup(game->map.data[r]);
		if (!tmp[r])
			err_handler(game, "Malloc fail\n");
		free(game->map.data[r]);
		r++;
	}
	tmp[r] = map_writer(game, line, i);
	tmp[r + 1] = NULL;
	if (game->map.rows > 0)
		free(game->map.data);
	game->map.data = tmp;
	game->map.rows++;
	return (0);
}
