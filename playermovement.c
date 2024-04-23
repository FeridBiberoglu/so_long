/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:18:52 by fbiberog          #+#    #+#             */
/*   Updated: 2024/04/23 21:48:20 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_position(struct t_data *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j][i])
	{
		if (game->map[j][i] == 'P')
		{
			game->x = i;
			game->y = j;
			return ;
		}
		i++;
		if (game->map[j][i] == '\0')
		{
			i = 0;
			j++;
		}
	}
}

void	collected(struct t_data *game)
{
	static int	i = 0;

	game->collectibles = game->collectibles - 1;
	game->map[game->y][game->x] = '0';
	if (i % 4 == 0)
		ft_printf("Messi leaving Sergio Ramos in the dust.\n");
	if (i % 4 == 1)
		ft_printf("Messi Messi Messi\n");
	if (i % 4 == 2)
		ft_printf("Encara Messi Encara Messi Encara Messi Encara Messi.\n");
	if (i % 4 == 3)
		ft_printf("Messi showing us why he is the best.\n");
	i++;
	return ;
}

void	pressed_key(mlx_key_data_t keydata, struct t_data *game)
{
	static int	moves = 0;
	static int	pos_check = 0;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		pos_check = game->y + game->x;
		if (keydata.key == MLX_KEY_W)
			move_player(game, -1, 'y');
		if (keydata.key == MLX_KEY_A)
			move_player(game, -1, 'x');
		if (keydata.key == MLX_KEY_S)
			move_player(game, 1, 'y');
		if (keydata.key == MLX_KEY_D)
			move_player(game, 1, 'x');
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (pos_check != (game->y + game->x))
		{
			moves++;
			ft_printf("Dribbles: %d\n", moves);
		}
		if (game->map[game->y][game->x] == 'C')
			mlx_close_window(game->mlx);
	}
	return ;
}

void	move_player(struct t_data *game, int dir, char dim)
{
	if (dim == 'x' && game->map[game->y][game->x + dir] != '1')
	{
		if (game->map[game->y][game->x + dir] == 'E' && game->collectibles > 0)
			return ;
		mlx_image_to_window(game->mlx, game->img0, (game->x * 64), (game->y
				* 64));
		game->x = game->x + dir;
		mlx_image_to_window(game->mlx, game->imgp, (game->x * 64), (game->y
				* 64));
	}
	if (dim == 'y' && game->map[game->y + dir][game->x] != '1')
	{
		if (game->map[game->y + dir][game->x] == 'E' && game->collectibles > 0)
			return ;
		mlx_image_to_window(game->mlx, game->img0, (game->x * 64), (game->y
				* 64));
		game->y = game->y + dir;
		mlx_image_to_window(game->mlx, game->imgp, (game->x * 64), (game->y
				* 64));
	}
	if (game->map[game->y][game->x] == 'C')
		collected(game);
	if (game->map[game->y][game->x] == 'E')
		mlx_close_window(game->mlx);
	return ;
}
