/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:18:52 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/15 19:54:04 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	norminette_function(struct t_data *game)
{
	mlx_texture_t	*texture_x;

	texture_x = mlx_load_png("textures/messionball.png");
	game->imgx = mlx_texture_to_image(game->mlx, texture_x);
	mlx_delete_texture(texture_x);
}

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

void	pressed_key(mlx_key_data_t keydata, struct t_data *game)
{
	static int	moves = 0;
	static int	pos_check = 0;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		pos_check = game->y + game->x;
		if (keydata.key == MLX_KEY_W)
			move_player_y(game, -1);
		if (keydata.key == MLX_KEY_A)
			move_player_x(game, -1);
		if (keydata.key == MLX_KEY_S)
			move_player_y(game, 1);
		if (keydata.key == MLX_KEY_D)
			move_player_x(game, 1);
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
