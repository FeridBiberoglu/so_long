/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:47:09 by fbiberog          #+#    #+#             */
/*   Updated: 2024/05/15 19:53:29 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <bsd/string.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct t_data
{
	void		*mlx;
	char		**map;
	int			fd;
	int			width;
	int			height;
	int			y;
	int			x;
	int			collectibles;
	int			exit_check;
	mlx_image_t	*img0;
	mlx_image_t	*img1;
	mlx_image_t	*imgc;
	mlx_image_t	*imge;
	mlx_image_t	*imgp;
	mlx_image_t	*imgx;
}				t_data;

void			pressed_key(mlx_key_data_t keydata, struct t_data *game);
char			*character_check(char *map, struct t_data *game);
int				measurements(char *map, struct t_data *game);
char			**ft_split2(char const *s, char c);
void			ft_free2(char **str, int j);
int				display_map(struct t_data *game);
void			move_player(struct t_data *game, int direction, char dimension);
int				floodfill(struct t_data *game);
int				ft_printf(const char *string, ...);
// void			player_position(struct t_data *game);
void			move_player_y(struct t_data *game, int dir);
void			move_player_x(struct t_data *game, int dir);
void			norminette_function(struct t_data *game);

#endif