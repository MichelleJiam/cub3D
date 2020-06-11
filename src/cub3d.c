/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 14:57:38 by mjiam         #+#    #+#                 */
/*   Updated: 2020/06/09 16:10:41 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		updater(t_game *game)
{
	if (game->keys.key_up || game->keys.key_dw || game->keys.key_lf ||
		game->keys.key_rt || game->keys.key_rotr || game->keys.key_rotl)
	{
		if (game->keys.key_up)
			mover_ud(&game->map, &game->player, &game->view, 1);
		if (game->keys.key_dw)
			mover_ud(&game->map, &game->player, &game->view, -1);
		if (game->keys.key_lf)
			mover_lr(&game->map, &game->player, &game->view, -1);
		if (game->keys.key_rt)
			mover_lr(&game->map, &game->player, &game->view, 1);
		if (game->keys.key_rotr)
			turner(&game->view, 1);
		if (game->keys.key_rotl)
			turner(&game->view, -1);
		game->frame = (game->frame < 99) ? game->frame + 1 : 2;
		render_map(game);
	}
	return (0);
}

void	init_mlx(t_game *game)
{
	if (!game->save)
		game->mlx_win = mlx_new_window(game->mlx, game->config.screenwidth,
						game->config.screenheight, "cub3D");
	game->fr1.ptr = mlx_new_image(game->mlx, game->config.screenwidth,
						game->config.screenheight);
	game->fr2.ptr = mlx_new_image(game->mlx, game->config.screenwidth,
						game->config.screenheight);
	game->fr1.addr = mlx_get_data_addr(game->fr1.ptr, &game->fr1.bpp,
						&game->fr1.linesize, &game->fr1.endian);
	game->fr2.addr = mlx_get_data_addr(game->fr2.ptr, &game->fr2.bpp,
						&game->fr2.linesize, &game->fr2.endian);
	if ((!game->save && !game->mlx_win) || !game->fr1.ptr || !game->fr2.ptr)
		err_handler(game, "Initialisation failed\n");
}

int		main(int argc, char **argv)
{
	t_game		game;
	int			save;

	save = 0;
	if (arg_checker(&game, argc, argv) > 0)
		save = 1;
	if (init_game(&game, save) < 0)
		err_handler(&game, "Initialisation failed\n");
	if (parser(&game, argv[1]) < 0)
		err_handler(&game, "File parsing failed\n");
	init_mlx(&game);
	render_map(&game);
	mlx_hook(game.mlx_win, 17, 1L << 17, exiter, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, keypress, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, keyrelease, &game);
	mlx_loop_hook(game.mlx, &updater, &game);
	mlx_loop(game.mlx);
	return (0);
}
