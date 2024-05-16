/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermovement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:40:44 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/16 17:18:39 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collected(struct t_data *game)
{
	static int	i = 0;

	game->collectibles = game->collectibles - 1;
	game->map[game->y][game->x] = '0';
	if (i % 4 == 0)
		ft_printf("Error\nMessi leaving Sergio Ramos in the dust.\n");
	if (i % 4 == 1)
		ft_printf("Error\nMessi Messi Messi\n");
	if (i % 4 == 2)
	{
		ft_printf("Error\n");
		ft_printf("Encara Messi Encara Messi Encara Messi Encara Messi.\n");
	}
	if (i % 4 == 3)
		ft_printf("Error\nMessi showing us why he is the best.\n");
	i++;
	return ;
}

void	from_exit(struct t_data *game, int dir, char dimension)
{
	mlx_image_to_window(game->mlx, game->imge, (game->x * 64), (game->y * 64));
	if (dimension == 'x')
		game->x = game->x + dir;
	else
		game->y = game->y + dir;
	mlx_image_to_window(game->mlx, game->imgp, (game->x * 64), (game->y * 64));
	if (game->map[game->y][game->x] == 'C')
		collected(game);
	if (game->map[game->y][game->x] == 'E' && game->collectibles == 0)
		mlx_close_window(game->mlx);
	return ;
}

void	to_exit(struct t_data *game, int dir, char dimension)
{
	mlx_image_to_window(game->mlx, game->img0, (game->x * 64), (game->y * 64));
	if (dimension == 'x')
		game->x = game->x + dir;
	else
		game->y = game->y + dir;
	mlx_image_to_window(game->mlx, game->imgx, (game->x * 64), (game->y * 64));
	if (game->map[game->y][game->x] == 'C')
		collected(game);
	if (game->map[game->y][game->x] == 'E' && game->collectibles == 0)
		mlx_close_window(game->mlx);
	return ;
}

void	move_player_x(struct t_data *game, int dir)
{
	if (game->map[game->y][game->x + dir] == '1')
		return ;
	if (game->map[game->y][game->x] == 'E')
	{
		from_exit(game, dir, 'x');
		return ;
	}
	if (game->map[game->y][game->x + dir] == 'E')
	{
		to_exit(game, dir, 'x');
		return ;
	}
	mlx_image_to_window(game->mlx, game->img0, (game->x * 64), (game->y * 64));
	game->x = game->x + dir;
	mlx_image_to_window(game->mlx, game->imgp, (game->x * 64), (game->y * 64));
	if (game->map[game->y][game->x] == 'C')
		collected(game);
	if (game->map[game->y][game->x] == 'E' && game->collectibles == 0)
		mlx_close_window(game->mlx);
	return ;
}

void	move_player_y(struct t_data *game, int dir)
{
	if (game->map[game->y + dir][game->x] == '1')
		return ;
	if (game->map[game->y][game->x] == 'E')
	{
		from_exit(game, dir, 'y');
		return ;
	}
	if (game->map[game->y + dir][game->x] == 'E')
	{
		to_exit(game, dir, 'y');
		return ;
	}
	mlx_image_to_window(game->mlx, game->img0, (game->x * 64), (game->y * 64));
	game->y = game->y + dir;
	mlx_image_to_window(game->mlx, game->imgp, (game->x * 64), (game->y * 64));
	if (game->map[game->y][game->x] == 'C')
		collected(game);
	if (game->map[game->y][game->x] == 'E' && game->collectibles == 0)
		mlx_close_window(game->mlx);
	return ;
}
