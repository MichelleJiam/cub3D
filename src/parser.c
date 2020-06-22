/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:44:23 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/19 14:44:09 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_copier(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		map[i] = ft_strdup(game->map.data[i]);
		if (!map[i])
			err_handler(game, "Malloc fail\n");
		i++;
	}
	map[i] = NULL;
}

int		finish_parse(t_game *game)
{
	double	*tmp;
	char	*map[game->map.rows + 1];
	int		i;

	i = 0;
	if (!game->map.data)
		err_handler(game, "Missing map\n");
	if (game->player.startdir == NONE)
		err_handler(game, "Missing starting position\n");
	map_copier(game, map);
	map_checker(game, map, game->player.pos.x, game->player.pos.y);
	game->player.quest = game->map.spritenum;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	tmp = malloc(sizeof(double) * game->config.screenwidth);
	if (!tmp)
		err_handler(game, "Malloc fail\n");
	game->map.perpdist = tmp;
	return (0);
}

int		fc_filler(t_game *game, char *line, int *i)
{
	if (line[*i + 1] == '-')
		err_handler(game, "Invalid floor/ceiling values\n");
	if (line[*i] == 'F' && (line[*i + 1] == ' ' || isnumber(line, *i + 1)))
	{
		(*i)++;
		whitespaceskip(line, i);
		if (isnumber(line, *i) || line[*i] == '-')
			return (colour_setter(game, &game->config.floor, line, i));
		return (tex_setter(game, &game->config.tex[F], line, i));
	}
	else if (line[*i] == 'C' && (line[*i + 1] == ' ' || isnumber(line, *i + 1)))
	{
		(*i)++;
		whitespaceskip(line, i);
		if (isnumber(line, *i) || line[*i] == '-')
			return (colour_setter(game, &game->config.ceiling, line, i));
		return (tex_setter(game, &game->config.tex[C], line, i));
	}
	return (-1);
}

int		data_filler(t_game *game, char *line)
{
	int		i;

	i = 0;
	whitespaceskip(line, &i);
	if (line[i] == 'R' && (line[i + 1] == ' ' || isnumber(line, i + 1) ||
		line[i + 1] == '-'))
		return (res_setter(game, line, &i));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (tex_setter(game, &game->config.tex[N], line, &i));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (tex_setter(game, &game->config.tex[S], line, &i));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (tex_setter(game, &game->config.tex[W], line, &i));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (tex_setter(game, &game->config.tex[E], line, &i));
	else if (line[i] == 'S' && line[i + 1] != '0')
		return (tex_setter(game, &game->config.sprite, line, &i));
	else if (line[i] == 'F' || line[i] == 'C')
		return (fc_filler(game, line, &i));
	else if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		return (map_maker(game, line, &i));
	else if (line[i] == '\0' && game->config.map_found)
		return (map_maker(game, line, &i));
	return (!line[i] ? 0 : -1);
}

int		parser(t_game *game, char *map)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		err_handler(game, "Failed to open map file\n");
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (data_filler(game, line) < 0)
			err_handler(game, "Invalid line in map file\n");
		free(line);
	}
	close(fd);
	if (finish_parse(game) < 0)
		return (-1);
	return (0);
}
