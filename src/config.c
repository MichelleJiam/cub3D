/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:48:02 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/11 18:06:22 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		colour_setter(t_game *game, t_colour *element, char *line, int *i)
{
	int rgb[3];
	int	c;

	c = 0;
	if (element->colour)
		err_handler(game, "Duplicate information (f/c) in map file\n");
	if (value_finder(line, i, line[*i]) < 0)
		return (-1);
	while (line[*i] && c < 3)
	{
		rgb[c] = ft_atoi(line, i);
		if (rgb[c] < 0 || rgb[c] > 255)
			err_handler(game, "Invalid floor/ceiling values\n");
		if (value_finder(line, i, ',') < 0)
			return (-1);
		c++;
	}
	element->colour = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	game->config.i++;
	return (0);
}

/*
** resolution is kept if --save is indicated
*/

int		res_setter(t_game *game, char *line, int *i)
{
	int maxwidth;
	int maxheight;

	if (game->config.screenwidth != 0 || game->config.screenheight != 0)
		err_handler(game, "Duplicate information (res) in map file\n");
	mlx_get_screen_size(game->mlx, &maxwidth, &maxheight);
	maxwidth = (maxwidth <= 0) ? 2560 : maxwidth;
	maxheight = (maxheight <= 0) ? 1400 : maxheight;
	if (value_finder(line, i, line[*i]) < 0)
		return (-1);
	game->config.screenwidth = ft_atoi(line, i);
	if (game->config.screenwidth > maxwidth && !game->save)
		game->config.screenwidth = maxwidth;
	game->config.screenheight = ft_atoi(line, i);
	if (game->config.screenheight > maxheight && !game->save)
		game->config.screenheight = maxheight;
	if (game->config.screenwidth <= 0 || game->config.screenheight <= 0)
		err_handler(game, "Invalid resolution\n");
	if (game->config.screenwidth > 16384 || game->config.screenheight > 16384)
		err_handler(game,
				"Resolution exceeds maximum (16384) for bitmap rendering\n");
	game->config.i++;
	return (0);
}

void	tex_filer(t_game *game, char *path, t_img *tex)
{
	int		format;

	format = -1;
	format = file_checker(2, path);
	if (format == -1)
		err_handler(game, "Invalid texture file\n");
	if (file_checker(3, path) < 0)
		err_handler(game, "Failed to open texture file\n");
	if (format == xpm)
		tex->ptr = mlx_xpm_file_to_image(game->mlx, path,
					&tex->width, &tex->height);
	else if (format == png)
		tex->ptr = mlx_png_file_to_image(game->mlx, path,
					&tex->width, &tex->height);
	if (tex->ptr == NULL)
		err_handler(game, "Image reading fail\n");
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp,
					&tex->linesize, &tex->endian);
	if (tex->addr == NULL)
		err_handler(game, "Image address retrieval fail\n");
}

char	*pathfinder(char *line, int *i, int len)
{
	char	*path;
	int		j;

	j = 0;
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (0);
	while (line[*i] && j < len)
	{
		path[j] = line[*i];
		j++;
		(*i)++;
	}
	path[j] = '\0';
	return (path);
}

int		tex_setter(t_game *game, t_img *tex, char *line, int *i)
{
	char	*path;
	int		len;

	len = 0;
	path = NULL;
	if (tex->ptr)
		err_handler(game, "Duplicate information (tex) in map file\n");
	if (inset(line, *i))
	{
		while (!whitespaceskip(line, i))
			(*i)++;
	}
	whitespaceskip(line, i);
	while (line[*i + len] && line[*i + len] != '\n')
		len++;
	path = pathfinder(line, i, len);
	if (!path)
		err_handler(game, "Malloc fail\n");
	tex_filer(game, path, tex);
	free(path);
	game->config.i++;
	return (0);
}
